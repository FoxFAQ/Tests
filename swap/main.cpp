#include <iostream>

//using namespace std;

template<class T>
void swap(T& a, T& b)
{
    //00000101
    //00001000
    a ^= b;
    b ^= a;
    a ^= b;

}

template<class T>
void reset(T& a, unsigned int bitNum)
{
    a &= ~(1u << bitNum);
}

template<class T>
void set(T& a, unsigned int bitNum)
{
    a = a | (1u << bitNum);
}


int main()
{
    std::cout << "Hello World!" << std::endl;
    int x = 5;
    int y = 8;
    swap(x, y);
    std::cout << x << " " << y << std::endl;

    int a = 5;
    reset(a, 2);
    std::cout << a << std::endl;
    return 0;
}
