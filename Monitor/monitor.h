#ifndef MONITOR_H
#define MONITOR_H

#include "sensor.h"

class Monitor
{
public:
    Monitor(const std::vector<Sensor*> &sensors);
    void checkSensors(int value);
    void stopChecking();
private:
    std::vector<Sensor*> sensors_;
    bool checking_ = false;
};

#endif // MONITOR_H
