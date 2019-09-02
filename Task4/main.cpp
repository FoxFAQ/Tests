#include <iostream>
#include <vector>
using namespace std;

struct Car
{
    int weight = 0;
    int volume = 0;
};

struct Cargo
{
    int weight = 0;
    int volume = 0;
};

template<typename T, typename A>
void increment(vector<T, A> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] += 1;
    }
}

template <>
void increment(vector<Car> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].volume += 1;
        vec[i].weight += 1;
    }
}

template <>
void increment(vector<Cargo> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].volume += 1;
        vec[i].weight += 1;
    }
}

int main()
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    increment<int>(vec);
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << endl;

    Car temp;
    vector<Car> vecCar;
    vecCar.push_back(temp);
    vecCar.push_back(temp);
    increment<Car>(vecCar);
    for (int i = 0; i < vecCar.size(); i++)
        cout << vecCar[i].weight << " " << vecCar[i].volume << endl;

    //THE SAME STUFF FOR CARGO

    return 0;
}
