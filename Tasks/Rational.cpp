#include <iostream>

using namespace std;

struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;
    
    Rational &operator+=(const Rational &rational) {
    	this->add(rational);
    	return *this;
    }
    Rational &operator-=(const Rational &rational) {
    	this->sub(rational);
    	return *this;
    }
    Rational &operator*=(const Rational &rational) {
    	this->mul(rational);
    	return *this;
    }
    Rational &operator/=(const Rational &rational) {
    	this->div(rational);
    	return *this;
    }
    
    Rational operator-() const {
        Rational r(*this);
        r.neg();
        return r;
     }
    Rational operator+() const {
        return *this;
     }
     
     friend bool operator==(const Rational &rval, const Rational &lval);
     friend bool operator<(const Rational &rval, const Rational &lval);
     
     operator double() const {
     	return this->to_double();
     }
     
private:
    int numerator_;
    unsigned denominator_;
};

Rational operator+(Rational rval, const Rational &lval) {
	return rval += lval;
}
Rational operator-(Rational rval, const Rational &lval) {
	return rval -= lval;
}
Rational operator*(Rational rval, const Rational &lval) {
	return rval *= lval;
}
Rational operator/(Rational rval, const Rational &lval) {
	return rval /= lval;
}

bool operator==(const Rational &rval, const Rational &lval) {
	return (rval.numerator_ == lval.numerator_ && rval.denominator_ == lval.denominator_);
}
bool operator!=(const Rational &rval, const Rational &lval) {
	return !(rval == lval);
}
bool operator<(const Rational &rval, const Rational &lval) {
	return ((int)rval.numerator_ * (int)lval.denominator_ < (int)lval.numerator_ * (int)rval.denominator_);
}
bool operator<=(const Rational &rval, const Rational &lval) {
	return !(lval < rval);
}
bool operator>(const Rational &rval, const Rational &lval) {
	return (lval < rval);
}
bool operator>=(const Rational &rval, const Rational &lval) {
	return !(rval < lval);
}

int main(int argc, char const *argv[])
{
	//cout << "Hello\n";
	{
		Rational r1(2, 2);
		Rational r2(2, 4);

		cout << "+=: Rational, Rational\n";
		r1 += r2;
		r1.show();

		cout << "+=: Rational, int\n";
		r1 += 5;
		r1.show();
	}


	return 0;
}
