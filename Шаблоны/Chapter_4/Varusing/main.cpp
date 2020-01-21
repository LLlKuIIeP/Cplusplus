// 4.4.5 Вариативные базовые классы и using
#include <string>
#include <unordered_set>

class Customer
{
public:
    Customer(std::string const& n) : name(n) {}
    std::string getName() const
    {
        return name;
    }

private:
    std::string name;
};

struct CustomerEq
{
    bool operator()(Customer const& c1, Customer const& c2) const
    {
        return c1.getName() == c2.getName();
    }
};

struct CustomerHash
{
    std::size_t operator()(Customer const& c) const
    {
        return std::hash<std::string>()(c.getName());
    }
};

// Объедиение класса, который объдиняет operator()
// для вариативных базовых классов
template<typename... Bases>
struct Overloader : Bases...
{
    using Bases::operator()...;
};

int main()
{
    using CustomerOP = Overloader<CustomerHash, CustomerEq>;
    std::unordered_set<Customer, CustomerHash, CustomerEq> col1;
    std::unordered_set<Customer, CustomerOP, CustomerOP> col2;

    return 0;
}
