#include <iostream>
#include <vector>

using namespace std;

class BasicCar
{
    int volume_ = INT_MAX;
    int weight_ = INT_MAX;

public:
    BasicCar() {}
    BasicCar(int weight, int volume) : volume_(volume), weight_(weight) {}
    virtual ~BasicCar() {}

    virtual int getWeight() const {return weight_;}
    virtual void setWeight(int value) {weight_ = value;}
    virtual int getVolume() const {return volume_;}
    virtual void setVolume(int value) {volume_ = value;}
};

class CarWeightVolume : public BasicCar
{
    int volume_ = 0;
    int weight_ = 0;

public:
    CarWeightVolume(int weight, int volume) : volume_(volume), weight_(weight) {}
    virtual ~CarWeightVolume() {}

    virtual int getWeight() const {return weight_;}
    virtual void setWeight(int value) {weight_ = value;}
    virtual int getVolume() const {return volume_;}
    virtual void setVolume(int value) {volume_ = value;}
};

class CarWeight : public BasicCar
{
    int weight_ = 0;

public:
    CarWeight(int weight) : weight_(weight) {}
    virtual ~CarWeight() {}
    virtual int getWeight() const {return weight_;}
    virtual void setWeight(int value) {weight_ = value;}
};

int main()
{
    CarWeightVolume car1(100, 500);
    CarWeightVolume car2(200, 100);

    CarWeight car3(50);
    CarWeight car4(500);

    vector<BasicCar*> cars;
    cars.push_back(&car1);
    cars.push_back(&car2);
    cars.push_back(&car3);
    cars.push_back(&car4);

    for (int i = 0; i < cars.size(); i++)
        cout << cars.at(i)->getWeight() << " " << cars.at(i)->getVolume() << endl;
    cout << endl;

    ///////////////////Removing///////////
    int cargoWeight = 100;
    int cargoVolume = 200;

    for(int i = cars.size() - 1; i >= 0; i--)
    {
        if(cars.at(i)->getWeight() < cargoWeight || cars.at(i)->getVolume() < cargoVolume)
            cars.erase(cars.begin()+i);
    }

    for (int i = 0; i < cars.size(); i++)
        cout << cars.at(i)->getWeight() << " " << cars.at(i)->getVolume() << endl;

    return 0;
}
