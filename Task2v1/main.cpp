#include <QCoreApplication>
#include "recursive_shared_mutex.h"
#include <QElapsedTimer>
#include <QReadWriteLock>
#include <QDebug>

recursive_shared_mutex mutex;
QReadWriteLock lock(QReadWriteLock::Recursive);

void readFunction()
{
    mutex.lock_shared();
    mutex.lock_shared();
    for (int i = 0; i < 1000; i++)
    {
        qDebug() << std::hash<std::thread::id>{}(std::this_thread::get_id()) << i;
    }
    mutex.unlock_shared();
    mutex.unlock_shared();
}

void readFunctionQt()
{
    lock.lockForRead();
    lock.lockForRead();
    for (int i = 0; i < 1000; i++)
    {
        qDebug() << std::hash<std::thread::id>{}(std::this_thread::get_id()) << i;
    }
    lock.unlock();
    lock.unlock();
}

void writeFunction()
{
    mutex.lock();
    mutex.lock();
    for (int i = 0; i < 1000; i++)
    {
        qDebug() << std::hash<std::thread::id>{}(std::this_thread::get_id()) << i;
    }
    mutex.unlock();
    mutex.unlock();
}

void writeFunctionQt()
{
    lock.lockForWrite();
    lock.lockForWrite();
    for (int i = 0; i < 1000; i++)
    {
        qDebug() << std::hash<std::thread::id>{}(std::this_thread::get_id()) << i;
    }
    lock.unlock();
    lock.unlock();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QElapsedTimer timer;
    timer.start();

//    std::thread t1(readFunction);
//    std::thread t2(readFunction);
//    std::thread t3(readFunction);
//    std::thread t4(readFunction);
//    std::thread t1(writeFunction);
//    std::thread t2(writeFunction);
//    std::thread t3(writeFunction);
//    std::thread t4(writeFunction);

//    std::thread t1(readFunctionQt);
//    std::thread t2(readFunctionQt);
//    std::thread t3(readFunctionQt);
//    std::thread t4(readFunctionQt);
    std::thread t1(writeFunctionQt);
    std::thread t2(writeFunctionQt);
    std::thread t3(writeFunctionQt);
    std::thread t4(writeFunctionQt);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    qDebug() << "Finished threads msecs" << timer.elapsed();

    return a.exec();
}
