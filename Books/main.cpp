#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <chrono>
#include <queue>
#include <future>


void hello() {
	std::cout << "function: hello()\n";
}

class background_task {
public:
	void operator()() {
		std::cout << "call operator() in class\n";
	}
};


//	2
namespace chapter_2 {
	void some_update(std::vector<int> &v) {
		for(auto &elem : v) {
			elem *= 2;
		}
	}

	class A {
		public:
			void some() {
				std::cout << "call method in class A\n";
			}
	};
}



//	3
namespace chapter_3 {

	class Some_big_object {
		public:
			explicit Some_big_object(const int n) :x(n) {}
			friend void swap(Some_big_object &lhs, Some_big_object &rhs);
			void print() {
				std::cout << x << std::endl;
			}

		private:
			int x;
	};

        void swap(Some_big_object &lhs, Some_big_object &rhs) {
                std::swap(lhs.x, rhs.x);
        }


	class X {
		public:
			X(Some_big_object const &sd) :some_detail(sd) {}
			friend void swap(X &lhs, X &rhs);
			void print() {
				some_detail.print();
			}

		private:
			Some_big_object some_detail;
			std::mutex m;
	};

        void swap(X &lhs, X &rhs) {
                if(&rhs == &lhs) {
                        return;
                }

                std::lock(lhs.m, rhs.m);                                        // захват обоих мьютексов
                std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);     //      т.к. у функции нет деструктора, то конструируем объекты классов с доп параметром
                std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);     //      std::adopt_lock - мьютексы уже захвачены, поэтому нужно лишь принять владение существующей блокировкой
                swap(lhs.some_detail, rhs.some_detail);

	        /*
                другой вариант: потребляет больше памяти и более гибкий - std::unique_lock<std::mutex>
                std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);    //      std::defer_lock - оставить мьютексы не захваченными
                std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
                //      захватить мьютексы
                std::lock(lock_a, lock_b);
	        */
        }

	std::mutex some_mutex;
	std::unique_lock<std::mutex> get_lock() {
		extern std::mutex some_mutex;
		std::unique_lock<std::mutex> lk(some_mutex);
		std::cout << "lock mutex\n";

		//код
		return lk;	//	семантика перемещения = return std::move(lk);
	}

	void process_data() {
		std::unique_lock<std::mutex> lk(get_lock());
		std::cout << "move mutex\n";

		//код
	}

	//	защита разделяемых данных во время инициализации
	std::shared_ptr<int> resource_ptr;
	std::once_flag resource_flag;		//объекты этого типа нельзя копировать или перемещать

	void init_resource() {
		std::cout << "Поток с id=" << std::this_thread::get_id() << " инициализировал ресурс\n";
		resource_ptr.reset(new int);
	}

	//	инициализация производится всего один раз
	void foo() {
		std::call_once(resource_flag, init_resource);

		//код
	}

	class A {
		public:
			A() :x(0) {}
			void send_data() {
				std::call_once(init_flag, &A::init, this);
				//код
			}

                        void receive_data() {
                                std::call_once(init_flag, &A::init, this);
                                //код
                        }


		private:
			int x{0};
			std::once_flag init_flag;

			void init() {
				x = 1;
				std::cout << "Поток с id=" << std::this_thread::get_id() << " инициализировал ресурс(класс)\n";
			}
	};

}

//	4
namespace chapter_4 {
	std::mutex m;
	std::vector<int> v;
	std::condition_variable data_cond;

	void data_preparation_thread() {

		data_cond.notify_one();		//	ничего не произойдет, т.к. в другом потоке лямбда вернет false
		std::cout << "Поток 1: " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));	//	таймаут 3 секунды


		std::lock_guard<std::mutex> lk(m);
		for(int i = 0; i < 10; ++i) {
			v.push_back(i);
		}

                std::cout << "Поток 1: " << std::this_thread::get_id() << std::endl;
                data_cond.notify_one();
		//dara_cond.notify_all();	//	оповестить все потоки, которые ждут по wait()
	}

	void data_processing_thread() {
		while(true) {
			std::unique_lock<std::mutex> lk(m);
			std::cout << "Поток 2: " << std::this_thread::get_id() << std::endl;

			data_cond.wait(lk, [] () { return !v.empty(); } );
			std::cout << "Поток 2: " << std::this_thread::get_id() << std::endl;
			lk.unlock();

			if(v.size()) {
				break;
			}
		}
	}

	//	потокобезопасная обертка над очередью std::queue
	template<class T>
	class threadsafe_queue {
		public:
			threadsafe_queue() {}
			explicit threadsafe_queue(threadsafe_queue const &other) {
				std::lock_guard<std::mutex> lk(other.m);
				data_queue = other.data_queue;
			}

			void push(T new_value) {
				std::lock_guard<std::mutex> lk(m);
				data_queue.push(new_value);
				data_cond.notify_one();
			}

			void wait_and_pop(T &value) {
				std::unique_lock<std::mutex> lk(m);
				data_cond.wait(lk, [this] () { return !data_queue.empty(); } );
				std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
				data_queue.pop();
				return res;
			}

			bool try_pop(T &value) {
				std::lock_guard<std::mutex> lk(m);
				if(data_queue.empty()) {
					return false;
				}
				value = data_queue.front();
				data_queue.pop();
				return true;
			}

                        std::shared_ptr<T> try_pop() {
                                std::lock_guard<std::mutex> lk(m);
                                if(data_queue.empty()) {
                                        return std::shared_ptr<T>();
                                }
				std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
                                data_queue.pop();
                                return res;
                        }

			bool empty() {
				std::lock_guard<std::mutex> lk(m);
				return data_queue.empty();
			}


		private:
			mutable std::mutex m;
			std::queue<T> data_queue;
			std::condition_variable data_cond;
	};


	int find_the_answer_to_ltuae_1() {
		return 1;
	}
        int find_the_answer_to_ltuae_2(int n) {
                return n;
        }

	struct X {
		void foo(int n, std::string str) {
		}
		std::string bar(std::string str) {
			return str.append("_bar");
		}
	};

	struct Y {
		double operator() (double d) {
			return 1.1;
		}
	};

	class move_only {
		public:
			move_only() {}
			move_only(move_only&&) {}
			explicit move_only(move_only const &) = delete;
			move_only& operator=(move_only&&) { return *this; }
			move_only& operator=(move_only const) = delete;
			void operator() () {}
	};

	X baz(X &x) {
		return std::move(x);
	}

	int some_task() {
		return 0;
	}

	int do_something_with(int n) {
		std::cout << "Вызвали do_something_with\n";
		return 0;
	}

}







int main(int argc, char *argv[]) {

//ГЛАВА 1
{
	std::cout << "\n\tГлава 1\n";
	//	функцию в потоке
	std::thread t(hello);
	t.join();

	//	класс с перегруженным оператором круглые скобки
	background_task f;
	std::thread my_thread(f);
	my_thread.join();

	//	через конструктор временного объекта, двумя способами объявления переменной
	std::thread my_thread_1((background_task()));
	my_thread_1.join();

	std::thread my_thread_2{background_task()};
	my_thread_2.join();

	//	лямбда выражения, причем у лямбда есть захват локальных переменных
	std::thread my_thread_3([] {
		std::cout << "call lambda()\n";
	});
	my_thread_3.join();
}

//ГЛАВА 2 - Передача параметров
{
	using namespace chapter_2;
	std::cout << "\n\tГлава 2\n";
	//	колличество аппаратно поддерживаемых потоков машиной
	std::cout << "Максимальное число потоков поддерживаемых апаратно равно " << std::thread::hardware_concurrency() << std::endl;

	//	передача ссылок в поток
	std::vector<int> v;
		for(auto i = 0; i < 10; ++i) {
			v.push_back(i);
		}
	std::thread my_thread_4(some_update, std::ref(v));
	my_thread_4.join();
		for(auto &elem : v) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;

	//	передать указатель на член функцию
	A a;
	std::thread my_thread_5(&A::some, &a);
	my_thread_5.join();
}

//ГЛАВА 3 - Блокировки
{
	using namespace chapter_3;
	std::cout << "\n\tГлава 3\n";

	X x_a(Some_big_object(5));
	X x_b(Some_big_object(7));

        x_a.print();
        x_b.print();
	swap(x_a, x_b);
	x_a.print();
	x_b.print();


	//	перемещение мьютекса
	process_data();


	//	защита разделяемых данных во время инициализации
	std::thread thread_1(foo);
        std::thread thread_2(foo);
        std::thread thread_3(foo);
	thread_1.join();
        thread_2.join();
        thread_3.join();

	//	для классов
	A a;
        std::thread thread_4(&A::send_data, &a);
        std::thread thread_5(&A::send_data, &a);
        std::thread thread_6(&A::receive_data, &a);
        thread_4.join();
        thread_5.join();
        thread_6.join();
	//	с 11-го стандарта переменная static инициализируется потокобезопасно
}

//ГЛАВА 4 - Синхронизация
{
	using namespace chapter_4;
	std::cout << "\n\tГлава 4\n";
	std::thread thread_1(data_preparation_thread);
	std::thread thread_2(data_processing_thread);
	thread_1.join();
	thread_2.join();


	std::future<int> the_answer_1 = std::async(find_the_answer_to_ltuae_1);
	std::future<int> the_answer_2 = std::async(find_the_answer_to_ltuae_2, 5);
	std::cout << "Первый ответ равен: " << the_answer_1.get() << std::endl;
        std::cout << "Второй ответ равен: " << the_answer_2.get() << std::endl;

	X x;
	auto fut_1 = std::async(&X::foo, &x, 42, "hello");	//	вызывается через указатель p->foo(42, "hello"); где p = &x
	auto fut_2 = std::async(&X::bar, x, "goodbay");		//	вызывается через копированную ссылку tmpx.bar("goodbay"); где tmpx копия x
	std::cout << fut_2.get() << std::endl;

	Y y;
	auto fut_3 = std::async(Y(), 3.14);		//	вызывается tmpy(3.14), tmpy - создается из Y перемещающим конструктором
	auto fut_4 = std::async(std::ref(y), 3.14);	//	вызывается y(3.14)
	std::async(baz, std::ref(x));			//	вызывается baz(x)


	auto fut_5 = std::async(move_only());		//	вызывается tmp, где tmp конструируется с помощью std::move(move_only());

	auto fut_6 = std::async(std::launch::async, Y(), 1.2);			//	std::launch::async - параметр, который принудительно запускает фунцию в новом потоке
	auto fut_7 = std::async(std::launch::deferred, baz, std::ref(x));	//	выполнить при вызове wait() или get()

	//	на усмотрение реализации - запутить в основном или отдельых потоках
	auto fut_8 = std::async(std::launch::async | std::launch::deferred, baz, std::ref(x));
	auto fut_9 = std::async(baz, std::ref(x));

	fut_7.wait();		//	вызвать отложенную функцию

	// Время
//	std::cout << std::chrono::system_clock::now() << std::endl;
	//	стабильные часы
//	std::chrono::steady_clock
	//	интервал задается шаблонным классом
//	std::chrono::duration<>
	//	для явного преобразования одного интевала в другой
//	std::chrono::duration_cast<>

	//	ждать 35 мс
	std::future<int> fut_10 = std::async(some_task);
	auto res_fut_10 = fut_10.wait_for(std::chrono::milliseconds(35));

	if(res_fut_10 == std::future_status::ready) {	//	готово
		do_something_with(fut_10.get());
		std::cout << "Задача готова\n";
	}
	else if(res_fut_10 == std::future_status::timeout) {	//	истек таймаут
		std::cout << "Если истек таймаут\n";
	}
	else if(res_fut_10 == std::future_status::deferred) {
		std::cout << "Задача отложена\n";
	}




}


	return 0;
}
