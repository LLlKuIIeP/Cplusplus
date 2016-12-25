#include <iostream>
#include <map>

std::map<Expression *, unsigned int> Map;


struct Number;
struct BinaryOperation;

struct Visitor {
	virtual void visitNumber(Number const *number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const *operation) = 0;
	virtual ~Visitor() {}
};


struct Expression {
	virtual double evaluate() const = 0;
	virtual void visit(Visitor *visitor) const = 0;
	virtual ~Expression() {};
};

struct Number : Expression {
	Number(double value) : value(value) {}
	
	virtual double evaluate() const { return value; };
	double get_value() const { return value; }
	virtual void visit(Visitor *visitor) const { visitor->visitNumber(this); }

	private:
		double value;
};

struct BinaryOperation : Expression {
	BinaryOperation(Expression const *left, char op, Expression const *right) : left(left), op(op), right(right) {}

	virtual double evaluate() const {
		switch(op) {
			case '+': {
				return left->evaluate() + right->evaluate();
			}
			case '-': {
				return left->evaluate() - right->evaluate();
			}
			case '*': {
				return left->evaluate() * right->evaluate();
			}
			case '/': {
				if(right->evaluate()) {
					return left->evaluate() / right->evaluate();
				}
				else {
					break;
				}
			}
			default: {
				break;
			}
		}
	}

	Expression const *get_left() const { return left; }
	Expression const *get_right() const { return right; }
	char get_op() const { return op; }

	virtual void visit(Visitor *visitor) const { visitor->visitBinaryOperation(this); }

	~BinaryOperation() {
		delete left;
		delete right;
	}

	private:
		Expression const *left;
		Expression const *right;
		char op;
};


struct  PrintBinaryOperationsVisitor : Visitor {
	void visitNumber(Number const *number) {
		std::cout << number->get_value();
	}

	void visitBinaryOperation(BinaryOperation const *bop) {
		std::cout << "(";
		bop->get_left()->visit(this);
		std::cout << bop->get_op();
		bop->get_right()->visit(this);
		std::cout << ")";
	}
};

struct ScopedPtr {
	explicit ScopedPtr(Expression *ptr = 0) :ptr_(ptr) {}
	
	Expression* get() const {
		return ptr_;
	}

	Expression* release() {
		ptr_ = 0;
		return ptr_;
	}

	void reset(Expression *ptr = 0) {
		Expression *copy = ptr_;
		ptr_ = 0;
		return copy;
	}

	Expression& operator*() const {
		return *ptr_;
	}

	Expression* operator->() const {
		return ptr_;
	}


	~ScopedPtr() {
		delete ptr_;
	}

	private:
		ScopedPtr(const ScopedPtr&);
		ScopedPtr& operator=(const ScopedPtr&);

		Expression *ptr_;
};

struct SharedPtr {

	explicit SharedPtr(Expression *ptr = 0) {
		if(ptr != 0 && Map.find(ptr) != Map.end()) {
			Map[ptr]++;
		}
		else if(ptr != 0 && Map.find(ptr) == Map.end()) {
			Map[ptr] = 1;
		}
		ptr_ = ptr;
	}

	SharedPtr(const SharedPtr &s_ptr) {
		if(s_ptr.ptr_ != 0) {
			this->ptr_ = s_ptr.ptr_;
			Map[s_ptr.ptr_]++;
		}
		else if(s_ptr.ptr_ == 0) {
			this->ptr_ = s_ptr.ptr_;
		}
	}
	SharedPtr& operator=(const SharedPtr &s_ptr) {
		if(this != &s_ptr) {
			if(this->ptr_ != 0 && s_ptr.ptr_ != 0) {
				Map[this->ptr_]--;
				Map[s_ptr.ptr_]++;
				if(Map[this->ptr_] == 0) {
					delete this->ptr_;
					Map.erase(this->ptr_);
				}
				this->ptr_ = s_ptr.ptr_;
			}

			else if(this->ptr_ != 0 && s_ptr.ptr_ == 0) {
				Map[this->ptr_]--;
				if(Map[this->ptr_] == 0) {
					delete this->ptr_;
					Map.erase(this->ptr_);
				}
				this->ptr_ = s_ptr.ptr_;
			}

			else if(this->ptr_ == 0 && s_ptr.ptr_ != 0) {
				Map[s_ptr.ptr_]++;
				this->ptr_ = s_ptr.ptr_;
			}
		}
		return *this;
	}


	Expression* get() const {
		return ptr_;
	}
	void reset(Expression *ptr = 0) {
		if(this->ptr_ != ptr) {
			
			if(this->ptr_ != 0 && ptr != 0) {
				Map[this->ptr_]--;
				if(Map[this->ptr_] == 0) {
					delete this->ptr_;
					Map.erase(this->ptr_);
				}

				if(Map.find(ptr) != Map.end()) {
					Map[ptr]++;
				}
				else {
					Map[ptr] = 1;
				}
			}

			else if(this->ptr_ == 0 && ptr != 0) {
				if(Map.find(ptr) != Map.end()) {
					Map[ptr]++;
				}
				else {
					Map[ptr] = 1;
				}
			}

			else if(this->ptr_ != 0 && ptr == 0) {
				Map[this->ptr_]--;
				if(Map[this->ptr_] == 0) {
					delete this->ptr_;
					Map.erase(this->ptr_);
				}
			}

			this->ptr_ = ptr;
		}
	}



	Expression& operator*() const {
		return *ptr_;
	}
	Expression* operator->() const {
		return ptr_;
	}

	Expression *ptr_;
	~SharedPtr() {
		if(this->ptr_ != 0 && Map[this->ptr_] > 1) {
			Map[this->ptr_]--;
		}
		else if(this->ptr_ != 0 && Map[this->ptr_] == 1) {
			delete this->ptr_;
			Map.erase(this->ptr_);
		}
	}
	private:

};





int main(int argc, char const *argv[])
{
	Expression *sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
	Expression *expr = new BinaryOperation(new Number(3), '*', sube);

	std::cout << expr->evaluate() << std::endl;
	PrintBinaryOperationsVisitor visitor;
	expr->visit(&visitor);
	delete expr;
	
	Expression *ptr = new BinaryOperation(new Number(4.5), '/', new Number(0));
	std::cout << ptr->evaluate() << std::endl;
	delete ptr;


	return 0;
}


