#include <iostream>

struct ICloneable {
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() {}
};

template<class T>
struct ValueHolder : ICloneable {
	ValueHolder(const T &data) :data_(data) {}

	virtual ICloneable* clone() const {
		return new ValueHolder<T>(*this);
	}
	T data_;
};

int main(int argc, char const *argv[])
{
	ICloneable *first = new ValueHolder<int>(1313);
	
	return 0;
}
