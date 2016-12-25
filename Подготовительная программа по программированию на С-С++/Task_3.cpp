#include <iostream>
#include <cmath>

using namespace std;

class Vector {
public:
		Vector();
		explicit Vector(int);
		Vector(const Vector&);
		Vector& operator= (const Vector&);
		
		enum Sign { PLUS, MINUS };
		
		int& operator[] (int);
		int operator[] (int) const;
		
		int size() const { return sz; }
		void reserve(int);
		int capacity() const;
		void resize(int);
		void push_back(int);
		void close();
		
		int mod() const;
		int scalar(const Vector&);
		void indicium(const Vector&, Sign, Vector&);
		void multiplyConst(const int, Vector&);
		
		~Vector() {
			delete[] elem;
		}
private:
		int sz;
		int *elem;
		int space;
};

Vector::Vector() :sz(0), elem(0), space(0) {}

Vector::Vector(int n)
:sz(n), elem(new int[n]) { 
	for( int i = 0; i < n; i++ ) {
		elem[i] = 0;
	}
}

Vector::Vector(const Vector &v) {
sz = v.sz;
	for( int i = 0; i < v.sz; i++ ) {
		elem[i] = v.elem[i];
	}

}

Vector& Vector::operator= (const Vector &v) {
	int *mas = new int[v.sz];
	for( int i = 0; i < v.sz; i++ ) {
		mas[i] = v.elem[i];
	}
	delete[] elem;
	elem = mas;
	sz = v.sz;
	return *this;
}

int& Vector::operator[] (int n) {
return elem[n];
}

int Vector::operator[] (int n) const {
return elem[n];
}

void Vector::reserve(int newAlloc) {
	if( space >= newAlloc ) {
		return;
	}
	int *mas = new int[newAlloc];
	for( int i = 0; i < sz; i++) {
		mas[i] = elem[i];
	}
	delete[] elem;
	elem = mas;
	space = newAlloc;
}

int Vector::capacity() const {
return space;
}

void Vector::resize(int newSize) {
	reserve(newSize);
	for( int i = sz; i < newSize; i++) {
		elem[i] = 0;
	}
	sz = newSize;
}

void Vector::push_back(int n) {
	if(space == 0) {
		reserve(8);
	}
	else if (sz == space) {
		reserve(2*space);
	}
	elem[sz] = n;
	sz++;
}

void Vector::close() {
	if ( sz > 0 ) {
		sz = 0;
		space = 0;
		delete[] elem;
	}
}

int Vector::mod() const {
	int module = 0;
	for( int i = 0; i < sz; i++) {
		module += pow(elem[i], 2);
	}
	return sqrt(module);
}

int Vector::scalar(const Vector &v) {
	int sl = 0;
	if( sz != v.sz ) {
		std::cout << "Vectors have different dimensions." << std::endl;
		return 0;
	}
	for( int i = 0; i < sz; i++) {
		sl += elem[i]*v.elem[i];
	}
	return sl;
}

void Vector::indicium(const Vector &v, Sign operand, Vector& vSum) {
	int sm;
	if( sz != v.sz ) {
		std::cout << "Vectors have different dimensions." << std::endl;
		return;
	}
		
	vSum.close();
	if( operand == Sign::PLUS) { 
		for( int i = 0; i < sz; i++) {
			sm = 0;		
			sm = elem[i] + v.elem[i];
			vSum.push_back(sm);
		}
	}
	else if (operand == Sign::MINUS) {
		for( int i = 0; i < sz; i++) {
			sm = 0;		
			sm = elem[i] - v.elem[i];
			vSum.push_back(sm);
		}
	}
}

void Vector::multiplyConst(const int C, Vector &v) {
	int res;
	v.close();
	for( int i = 0; i < sz; i++) {
		res = elem[i]*C;
		v.push_back(res);
	}
}

bool collinear(const Vector &v1, const Vector &v2) {
	if( v1.size() != v2.size() ) {
		std::cout << "Vectors have different dimensions." << std::endl;
		return false;
	}
	else if( v1.size() != 0 ) {
		if( v1.mod() == 0 || v2.mod() == 0 ) {
			return true;
		}
		
		double quotient;
		for( int i = 0; i < v1.size(); i++ ) {
			if( v1[i] != 0 && v2[i] != 0) {
				quotient = (double)v1[i] / v2[i];
				break;
			}
		}
		for( int i = 0; i < v1.size(); i++ ) {
			if( v1[i] != quotient * v2[i] ){
				return false;
			}
		}
		return true;
	}
}

void setVector(Vector &v) {
	char c;
	int n;
	cin >> c;
	while( c != '(' ) {
		cin >> c;
		}
	
	while( c != ')' ) {
		switch(c) {
			case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				cin.putback(c);
				cin >> n;
				v.push_back(n);
				break;
			default:
				break;
		}
		cin >> c;
	}
}



int main() {

Vector v1;
setVector(v1);

Vector v2;
setVector(v2);

if( collinear(v1, v2) ) {
	cout << "yes" << endl;
}
else {
	cout << "no" << endl;
}

return 0;
}
