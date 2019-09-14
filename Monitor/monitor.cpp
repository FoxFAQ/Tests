#include "monitor.h"

Monitor::Monitor(const std::vector<Sensor*> &sensors) : sensors_(sensors)
{

}

void Monitor::checkSensors(int value)
{
    checking_ = true;
    while(checking_)
    {
        for(unsigned int i = 0; i < sensors_.size(); i++)
        {
            while(sensors_.at(i)->hasNewData())
            {
                if(sensors_.at(i)->checkSensor(value))
                    cout << "Sensor " << i+1 << " has critical value " << value << endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Monitor::stopChecking()
{
    checking_ = false;
}
