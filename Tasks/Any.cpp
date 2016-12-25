#include <iostream>

using namespace std;

class ICloneable {
public:
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() {}
};

template<class T>
class ValueHolder : public ICloneable {
public:
	ValueHolder(const T &data) :data_(data) {}

	virtual ICloneable* clone() const {
		return new ValueHolder<T>(*this);
	}
	T data_;
};


class Any {
public:
	Any() :data(NULL) {}

	template<class T>
	Any(const T &t) :data(new ValueHolder<T>(t)) {}

	Any(const Any &any) {
	        if(any.data != NULL) {
			    data = any.data->clone();
	        }
	        else {
	            data = NULL;
	        }
	}

	Any& operator=(const Any &any) {
		if(this != &any) {
			delete data;
			data = any.data->clone();
		}
		return *this;
	}

	template<class T>
	Any& operator=(const T &any) {
		delete data;
		data = new ValueHolder<T>(any);
		return *this;
	}

	template<class T>
	T* cast() const {
		if(data != NULL) {
			ValueHolder<T> *ptr = dynamic_cast<ValueHolder<T>*>(data);
			if(ptr == NULL) {
				return 0;
			}
			return &(ptr->data_);
		}
		return 0;
	}

	~Any() { delete data; }

private:
	ICloneable *data;
};


int main(int argc, char const *argv[])
{
	ICloneable *first = new ValueHolder<int>(1313);
	Any empty;
	Any i(10);
	cout << "[1] i      = " << i.cast<int>() << endl;
	Any copy(i);
	cout << "[2] copy   = " << copy.cast<int>() << endl;
	empty = copy;
	cout << "[3] empty  = " << empty.cast<int>() << endl;
	cout << "[3] *empty = " << *empty.cast<int>() << endl;
	empty = 0;
	cout << "[4] empty  = " << empty.cast<int>() << endl;
	cout << "[4] *empty = " << *empty.cast<int>() << endl;
	int *iptr = i.cast<int>();
	cout << "[5] iptr   = " << iptr << endl;
	char *cptr = i.cast<char>(); // cptr = 0
	// cout << "[6] cptr=" << cptr << endl; // undefined behavior for char * == 0
	cout << "[6] cptr   = " << (void*)cptr << endl;
	Any empty2;
	int *p = empty2.cast<int>();
	cout << "[7] p      = " << p << endl;
	Any a = 20;
	cout << "[8] a      = " << a.cast<int>() << endl;
	a=0;
	cout << "[9] a      = " << a.cast<int>() << endl;
	a = 'w';
	cout << "[10] a     = " << a.cast<char>() << endl; // overloaded operator << for char *
	cout << "[10] a     = " << (void *)a.cast<char>() << endl;
	return 0;
}
