#include <iostream>

struct Foo {
	void say() const {
		std::cout << "Foo say: " << msg << "\n";
	}

	protected:
		Foo(const char *msg) :msg(msg) {}

	private:
		const char *msg;
};


struct Bar : Foo {
	Bar(const char *s) :Foo(s) {}
};


Foo get_foo(const char* s) {
	Bar b(s);
	Foo f = b;
	return f;
}


void foo_says(const Foo &foo) {
	foo.say();
}




int main(int argc, char const *argv[])
{

	foo_says(get_foo("Hello"));
	return 0;
}
