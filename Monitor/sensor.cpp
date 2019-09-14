#include "sensor.h"

Sensor::Sensor() : writer_(0), reader_(0), run_(false)
{
    results_.resize(N);
}

Sensor::~Sensor()
{
    if(run_.load(std::memory_order_acquire))
        stop();
}

bool Sensor::checkSensor(int value)
{
    if(reader_ != writer_)
    {
        if(results_[reader_] == value)
        {
            reader_ = (reader_ + 1) % N;
            return true;
        }
        else
        {
            reader_ = (reader_ + 1) % N;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Sensor::hasNewData()
{
    return (reader_ != writer_);
}

void Sensor::stop()
{
    run_.store(false, std::memory_order_release);
    if(thread_.joinable())
        thread_.join();
}

void Sensor::start(int interval)
{
    if(run_.load(std::memory_order_acquire))
        stop();
    run_.store(true, std::memory_order_release);
    thread_ = std::thread([this, interval]()
    {
        while(run_.load(std::memory_order_acquire))
        {
            results_[writer_] = (rand() % 100) + 1;
            writer_ = (writer_ + 1) % N;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    });
}

bool Sensor::isRunning() const
{
    return (run_.load(std::memory_order_acquire) && thread_.joinable());
}
