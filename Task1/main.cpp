#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Car
{
    int weight = 100;
    int volume = 200;

    bool operator > (const Car& car) const
    {
        if(weight > car.weight)
            return true;
        else if(weight == car.weight)
            return (volume > car.volume);
        else
            return false;
    }
};

int main()
{
    vector<Car> cars;
    Car temp;
    cars.push_back(temp);

    for(int i = 0; i < 3; i++)
    {
        temp.weight = 100*i;
        temp.volume = 100*i;
        cars.push_back(temp);
    }

    for (int i = 0; i < cars.size(); i++)
        cout << cars.at(i).weight << " " << cars.at(i).volume << endl;
    cout << endl;

    sort(cars.begin(), cars.end(), greater<Car>());

    for (int i = 0; i < cars.size(); i++)
        cout << cars.at(i).weight << " " << cars.at(i).volume << endl;
    return 0;
}
