#include <iostream>
#include <map>
#include <iomanip>
#include <cmath>
#define PI 3.1415926535

using namespace std;

class Figure {
public:
		virtual double Area() = 0;
		virtual void show() = 0;
};

class Square : public Figure {
public:
		Square() :edge(0) {}
		Square(double s) :edge(s) {}
		
		double Area() {
			return edge * edge;
		}
		void show() {
			cout << "class Square:" << endl;
		}
private:
		double edge;
};

class Circle : public Figure {
public:
		Circle() :radius(0) {}
		Circle(double r) :radius(r) {}
		
		double Area() {
			return (2 * PI * radius);
		}
		void show() {
			cout << "class Circle:" << endl;
		}
private:
		double radius;
};

class Rectangle : public Figure {
public:
		Rectangle() :length(0), width(0) {}
		Rectangle(double l, double w) :length(l), width(w) {}

		double Area() {
			return length * width;
		}
		void show() {
			cout << "class Rectangle:" << endl;
		}
private:
		double length, width;
};



int main() {
	char key, sym;
	double edge, radius, length, width;
	multimap<int, Figure*> u_multimap;

	cin >> key;
	while(cin) {
		switch(key) {
			case 's':
				cin >> sym;
				cin >> edge; 
				u_multimap.insert(pair<char, Figure* >(1, new Square(edge)));
				break;
			case 'c': 
				cin >> sym;
				cin >> radius; 
				u_multimap.insert(pair<char, Figure* >(2, new Circle(radius)));
				break;
			case 'r':
				cin >> sym;
				cin >> length;
				cin >> sym;
				cin >> width;
				u_multimap.insert(pair<char, Figure* >(3, new Rectangle(length, width)));
				break;
			default:
				break;
		}
		cin >> key;
	}

auto it = u_multimap.begin();
while(true) {
	if( it != u_multimap.end() ) {
		cout << (floor(it->second->Area()*100))/100;
		it++;
		if( it != u_multimap.end() ) {
			cout << ", ";
		}
	}
	else {
		break;
	}

}

return 0;
}
