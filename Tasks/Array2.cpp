#include <cstddef>
#include <iostream>
#include <string>
using namespace std;
#include <new>

template <typename Tx>
struct X
{
	X()
	{
		this->x_ = new Tx();
		*this->x_ = 1;
	}
	X(const X& inX)
	{
		this->x_ = new Tx();  
		*this->x_ = *inX.x_;
	}
	~X() { delete this->x_; }
	friend std::ostream& operator<< (std::ostream& s, const X& obj) 
	{ 
		s << *(obj.x_);
		return s; 
	}
	void set(Tx i)
	{
		*(this->x_) = i;
	}
private:
	X& operator=(const X& inX);
	Tx *x_;
};
/******************************T E S T S*********************/
void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();

template <class T>
class Array {
	public:
		explicit Array(size_t size = 0, const T& value = T()) {
			sz = size;
			mas = static_cast<T*>(operator new[] (size * sizeof(T)));
			size_t i;
			for(i = 0; i < size; i++) {
				new(mas + i) T(value);
			}
		}

		Array(const Array &arr) {
			size_t i;
			sz = arr.sz;
			
			mas = static_cast<T*>(operator new[] (sz * sizeof(T)));
			for(i = 0; i < sz; i++) {
				new(mas + i) T(arr.mas[i]);
			}
		}

		size_t size() const {
			return sz;
		}

		Array<T>& operator=(const Array<T> &arr) {
			if(this != &arr && &arr != NULL) {
				size_t i, size;

				for(i = 0; i < sz; i++) {
					mas[i].~T();
				}
				operator delete[] (mas);

				sz = arr.sz;
				mas = static_cast<T*>(operator new[] (sz * sizeof(T)));
				for(i = 0; i < sz; i++) {
					new(mas + i) T(arr.mas[i]);
				}
			}
			return *this;
		}

		T& operator[](size_t n) {
			return mas[n];
		}
		const T& operator[](size_t n) const {
			return mas[n];
		}


	/// Add prnt() to Array class public methods:
		void prnt()
		{
			for (size_t i = 0; i < sz; ++i)
				cout << mas[i];
			cout << endl;
		}

		~Array() {
			size_t i;

			for(i = 0; i < sz; i++) {
				mas[i].~T();
			}
			operator delete[] (mas);
		}
	private:
		size_t sz;
		T *mas;
};


int main(int argc, char const *argv[])
{
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

	return 0;
}


void test0()
{
	cout << endl << "*****Test 0(primitives)**********" << endl;
	{
		cout << endl << "*****CHAR**********" << endl;
		Array<char> ar(size_t(5), '0');
		Array<char> x(size_t(4), '4');
		ar = x;
		ar.prnt();

		Array<char> x2(size_t(6), '6');
		ar = x2;
		ar.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****STRING**********" << endl;
		Array<string> cr(size_t(5), "0");
		Array<string> cx(size_t(4), "4");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(6), "6");
		cr = cx2;
		cr.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****INT**********" << endl;
		Array<int> ir(size_t(5), 0);
		Array<int> ix(size_t(4), 4);
		ir = ix;
		ir.prnt();

		Array<int> ix2(size_t(6), 6);
		ir = ix2;
		ir.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****DOUBLE**********" << endl;
		Array<double> dr(size_t(5), 0.0);
		Array<double> dx(size_t(4), 4.0);
		dr = dx;
		dx.prnt();

		Array<double> ix2(size_t(6), 6.0);
		dr = ix2;
		dr.prnt();
	}
	cout << endl;
	return;
}


void test1()
{
	{
		cout << endl << "*****Test 1(assigment)**********" << endl;
		Array<char> ar(size_t(100), '0');
		Array<char> x(size_t(0), '1');
		ar = x;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> cr(size_t(100), "Str0");
		Array<string> cx(size_t(0), "Str1");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(2), "Str3");
		cr = cx2;
		cr.prnt();
	}
	{
		cout << "*****INT**********" << endl;
		Array<int> cr(size_t(100), 0);
		Array<int> cx(size_t(0), 15);
		cr = cx;
		cr.prnt();

		Array<int> cx2(size_t(2), 55);
		cr = cx2;
		cr.prnt();
	}
	return;
}

void test2()
{
	cout << endl << "*****Test 2(copy constructor)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> x(size_t(3), '3');
		Array<char> ar(x);
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> x(size_t(3), "333");
		Array<string> ar(x);
		ar.prnt();
	}

	return;
}

void test3()
{
	cout << endl << "*****Test 3(Empty)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> ar(size_t(0), '0');
		ar = ar;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> ar(size_t(0), "0");
		ar = ar;
		ar.prnt();
	}
	return;
}

void test4()
{
	cout << endl << "*****Test 4(assigment A=A) **********" << endl;
	{
		Array<char> ar(size_t(4), '0');
		ar = ar;
		ar.prnt();
	}
	return;
}
void test5()
{
	cout << endl << "*****Test 5(out bound)**********" << endl;
	{
		cout << "*****more**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[10] << endl;
	}
	{
		cout << "*****less**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[-10] << endl;
	}
	return;
}

void test6()
{
	cout << endl << "*****Test 6(pointer)**********" << endl;
	{
		cout << "*****CHAR(copy)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(4), '4');
		ar->prnt();
		delete ar;
	}
	{
		cout << "*****CHAR(=)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(5), '5');
		ar->prnt();
		Array<char> *xr = ar;
		xr->prnt();
		delete ar;
	}
	return;
}

void test7()
{
	cout << endl << "*****Test 7(X-object)**********" << endl;
	{
		cout << "***** X<INT> **********" << endl;
		X<int> x;
		x.set(4);
		Array<X<int> > *ar = new Array<X<int> >(size_t(4), x);
		ar->prnt();
		delete ar;
	}
	{
		cout << "***** X<CHAR> (new, =, copy) **********" << endl;
		X<char> x;
		x.set('c');
		Array<X<char> > *ar = new Array<X<char> >(size_t(4), x);
		ar->prnt();
		Array<X<char> > *xr = ar;
		xr->prnt();
		Array<X<char> > y(*xr);
		y.prnt();
		delete ar;
	}
	{
		cout << "***** X<STRING> (new, =, copy)**********" << endl;
		X<string> x;
		x.set("There are no tests for this task");
		Array<X<string> > *ar = new Array<X<string> >(size_t(1),x );
		ar->prnt();
		Array<X<string> > *xr = ar;
		xr->prnt();
		Array<X<string> > y(*xr);
		y.prnt();
		delete ar;
		//cout << "end\n";
	}
	//cout << "end\n";
	return;
}
