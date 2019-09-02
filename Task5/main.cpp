#include <iostream>
#include <string>

using namespace std;

class Car
{
    int weight_ = 100;
    int volume_ = 100;
public:
    void print() {cout << weight_ << " " << volume_ << endl;}
};

class Cargo
{
    int weight_ = 200;
    int volume_ = 200;
public:
    void print() {cout << weight_ << " " << volume_ << endl;}
};

template <typename T>
class Name : public T
{
    string name_ = "name";
public:
    Name(const char* str) : name_(str) {}
    void print() {cout << name_ << " "; T::print();}
};

int main()
{
    Name<Car> car("BMW");
    Name<Cargo> cargo("Box");

    car.print();
    cargo.print();
    return 0;
}
