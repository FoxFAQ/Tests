#include "monitor.h"

int main()
{
    srand(0);
    std::vector<Sensor*> sensors;
    for (unsigned int i = 0; i < 10; i++)
    {
        sensors.push_back(new Sensor);
        sensors.at(i)->start(1000);
    }

    Monitor monitor(sensors);
    monitor.checkSensors(5);

    return 0;
}
