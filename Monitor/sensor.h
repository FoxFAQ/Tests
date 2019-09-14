#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>
#include <vector>

using namespace std;

class Sensor
{
public:
    Sensor();
    ~Sensor();

    bool checkSensor(int value);
    bool hasNewData();

    void stop();
    void start(int interval);
    bool isRunning() const;

private:
    const int N = 10;
    std::vector<int> results_;
    std::atomic<int> writer_;
    std::atomic<int> reader_;
    std::thread thread_;
    std::atomic<bool> run_;
};

#endif // SENSOR_H
