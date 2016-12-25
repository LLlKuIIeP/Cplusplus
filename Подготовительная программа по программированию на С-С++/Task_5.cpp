#include <iostream>
#include <vector>
#include <limits>
#include <typeinfo>
#include <cmath>
#include <string>

using namespace std;

class Exception: public exception {
public:
	Exception() {};
	explicit Exception(string s) :str(s) {};
	string what() {
		return str;
	}
private:
	string str;
};

template<class Re, class Im> class Complex: public Exception {
public:
	Complex() :real(0), imag(0) {};
	explicit Complex(Re &r) :real(r), imag(0) {};
	Complex(const Complex &c) :real(c.real), imag(c.imag) {};

	Complex(Re &r, Im &i) :real(r), imag(i) {};
	Complex(const Re &r, Im &i) :real(r), imag(i) {};
	Complex(Re &r, const Im &i) :real(r), imag(i) {};
	Complex(const Re &r, const Im &i) :real(r), imag(i) {};

	//Complex(Re &re) throw ""
	void Addition(Complex<Re, Im> &c) throw(Exception) {
		if( abs(c.real) > limitsReal.max() - abs(real) ) {
			throw Exception("Addition max for Re");
		}
		if( abs(c.imag) > limitsImag.max() - abs(imag) ) {
			throw Exception("Addition max fot Im");
		}
		real += c.real;
		imag += c.imag;
	}
	void Subtraction(Complex<Re, Im> &c) throw(Exception) {
		if( abs(c.real) < limitsReal.min() - abs(real) ) {
			throw Exception("Subtraction min for Re");
		}
		if( abs(c.imag) > limitsImag.min() - abs(imag) ) {
			throw Exception("Addition min fot Im");
		}
		real -= c.real;
		imag -= c.imag;
	}
	void Multiply(Complex<Re, Im> &c) throw(Exception) {
		if(c.real != 0 && real > limitsReal.max() / c.real ) {
			throw Exception("Multiply max fot Re");
		}
		if( c.imag != 0 && real > limitsImag.max() / c.imag ) {
			throw Exception("Multiply max fot Im");
		}
		if( real*c.real < limitsReal.min() + imag*c.imag ) {
			throw Exception("Multiply max fot operation \"*\"");
		}
		Re resR = real*c.real - imag*c.imag;
		Im resI = real*c.imag + imag*c.real;
		real = resR;
		imag = resI;
	}
	void Multiply(int &n) throw(Exception) {
		if( real > limitsReal.max() / n || real < limitsReal.min() / n ) {
			throw Exception("Multiply(int), max fot Re");
		}
		if( imag > limitsImag.max() / n || imag < limitsImag.min() / n ) {
			throw Exception("Multiply(int), max fot Im");
		}
		real *= n;
		imag *= n;
	}
	void Multiply(const int &n) throw(Exception) {
		if( real > limitsReal.max() / n || real < limitsReal.min() / n ) {
			throw Exception("Multiply(comst int), max fot Re");
		}
		if( imag > limitsImag.max() / n || imag < limitsImag.min() / n ) {
			throw Exception("Multiply(const int), max fot Im");
		}
		real *= n;
		imag *= n;
	}

	void show() throw() {
		cout << real << " " << imag << endl;
	}

	Complex<Re, Im> operator = (Complex<Re, Im> &c) throw() {
		real = c.real;
		imag = c.imag;
		return *this;
	}

	template<class _Re, class _Im>
	friend Complex<Re, Im> operator + (Complex<Re, Im>&, Complex<Re, Im>&);

	template<class _Re, class _Im>
	friend Complex<Re, Im> operator - (Complex<Re, Im>&, Complex<Re, Im>&);

	template<class _Re, class _Im>
	friend ostream& operator << (ostream&, Complex<Re, Im>&);

	Re ReturnRe() {
		return real;
	}
	Re ReturnIm() {
		return imag;
	}
private:
	Re real;
	Im imag;
	numeric_limits<Re> limitsReal;
	numeric_limits<Im> limitsImag;
};

template<class _Re, class _Im>
Complex<_Re, _Im> operator + (Complex<_Re, _Im> &c1, Complex<_Re, _Im> &c2) {
	Complex<_Re, _Im> *c = new Complex<_Re, _Im>;
	*c = c1;
	c->Addition(c2);
return *c;
}

template<class _Re, class _Im>
Complex<_Re, _Im> operator - (Complex<_Re, _Im> &c1, Complex<_Re, _Im> &c2) {
	Complex<_Re, _Im> *c = new Complex<_Re, _Im>;
	*c = c1;
	c->Subtraction(c2);
	return *c;
}

template<class _Re, class _Im>
ostream& operator << (ostream &os, Complex<_Re, _Im> &c) {
	os << "(" << c.ReturnRe() << "," << c.ReturnIm() << ")";
	return os;
}

template<class Re, class Im>
void Input(vector<Complex<Re, Im>> &v) throw() {
	char symbol;
	Re real;
	Im imag;

		cin >> symbol;
		while (symbol != '[') {
			cin >> symbol;
		}

		while (symbol != ']') {
			switch (symbol) {
			case '(':
				cin >> real >> symbol >> imag;
				v.push_back(Complex<Re, Im>(real, imag));
				break;
			default:
				break;
			}
			cin >> symbol;
		}
	//for (auto it = v.begin(); it != v.end(); it++) {
	//	cout << *it << " ";
	//}
	//cout << endl;
}

template<class Re, class Im>
void SumVectors(vector<Complex<Re, Im>> &v1, vector<Complex<Re, Im>> &v2) throw() {
	vector<Complex<Re, Im>> v;
	for (int i = 0; i < v1.size(); i++) {
		v.push_back(Complex<Re, Im>(v1[i] + v2[i]));
	}
	cout << "[";
	for (auto it = v.begin(); it != v.end(); it++) {
		cout << *it;
		if (it != v.end() - 1) {
			cout << ",";
		}
	}
	cout << "]";
}

int main() {
	try {
		vector<Complex<int, int>> v1, v2;
		Input(v1);
		Input(v2);
		SumVectors(v1, v2);
	}
	catch (Exception &e) {
		cerr << "Exception: " << e.what();
	}
	catch (bad_cast &e) {
		cerr << "bad_cast: " << e.what();
	}
	catch (bad_alloc &e) {
		cerr << "bad_alloc: " << e.what();
	}
	catch (bad_typeid &e) {
		cerr << "bad_typeid: " << e.what();
	}
	catch (...) {
		throw;
	}
	return 0;
}
