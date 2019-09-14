#include <iostream>

class A
{
public:
  A()
  {
    f();
  }
  ~A()
  {
    f();
  }
    int a;
  virtual void f()
  {
    std::cout << "A" << std::endl;
  }
};

class B : public A
{
public:
  B()
  {
    f();
  }
  ~B()
  {
    f();
  }
  int b;
  virtual void f()
  {
    std::cout << "B" << std::endl;
  }
};

void g(A* ptr_a )
{
    ptr_a->f();
}
int main()
{
  A a;
  B b;
  //g(&b); ->B
  return 0;
}
//a
//A
//a
//A
//b
//B
//B
//A
//A
