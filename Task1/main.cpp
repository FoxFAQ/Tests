#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QRandomGenerator>
#include <QTextStream>
#include <float.h>
#include <QStack>
#include <QElapsedTimer>

void fileSorting(const QString &fileNameStart)
{
    QVector<double> tempDoubleVector;
    tempDoubleVector.reserve(8000000);

    int iteration = 1;
    double min = std::numeric_limits<double>::max();
    double max = 0;
    double pivot = 0;

    const int croppedFileSize = 60*1024*1024;

    QFile newSortedFile("SortedFile.txt");
    if(!newSortedFile.open(QIODevice::Append))
        return;
    newSortedFile.resize(0);
    QTextStream outNewSortedFile(&newSortedFile);

    QStack<QString> fileNamesStack;
    fileNamesStack.push(fileNameStart);

    while(!fileNamesStack.isEmpty())
    {
        QString fileName = fileNamesStack.pop();
        QFile oldFile(fileName);
        if(!oldFile.open(QIODevice::ReadOnly))
            return;
        QDataStream oldFileDS(&oldFile);
        oldFileDS.setFloatingPointPrecision(QDataStream::DoublePrecision);
        oldFileDS.setVersion(QDataStream::Qt_5_12);

        pivot = (max-min)/2 + min;

        if(oldFile.size() < croppedFileSize)
        {
            //Sorting
            tempDoubleVector.clear();

            double tempDoubleWriting;
            while(!oldFileDS.atEnd())
            {
                oldFileDS >> tempDoubleWriting;
                tempDoubleVector << tempDoubleWriting;
            }
            std::sort(tempDoubleVector.begin(), tempDoubleVector.end());

            for(int i = 0; i < tempDoubleVector.size(); i++)
                outNewSortedFile << tempDoubleVector[i] << '\n';
        }
        else
        {
            //Cropping
            min = std::numeric_limits<double>::max();
            max = 0;

            QFile newFileMin("FileMin.dat");
            QFile newFileMax("FileMax.dat");

            if(!newFileMin.open(QIODevice::WriteOnly))
                return;
            QDataStream newFileMinDS(&newFileMin);
            newFileMinDS.setFloatingPointPrecision(QDataStream::DoublePrecision);
            newFileMinDS.setVersion(QDataStream::Qt_5_12);

            if(!newFileMax.open(QIODevice::WriteOnly))
                return;
            QDataStream newFileMaxDataStream(&newFileMax);
            newFileMaxDataStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
            newFileMaxDataStream.setVersion(QDataStream::Qt_5_12);

            double tempDouble;
            while(!oldFileDS.atEnd())
            {
                oldFileDS >> tempDouble;
                if(min > tempDouble)
                    min = tempDouble;
                if(max < tempDouble)
                    max = tempDouble;

                if(tempDouble <= pivot)
                    newFileMinDS << tempDouble;
                else
                    newFileMaxDataStream << tempDouble;
            }

            newFileMin.close();
            newFileMax.close();

            newFileMin.rename("FileMin_" + QString::number(iteration) + ".dat");
            newFileMax.rename("FileMax_" + QString::number(iteration) + ".dat");
            iteration++;

            fileNamesStack.push(newFileMax.fileName());
            fileNamesStack.push(newFileMin.fileName());
        }
        oldFile.close();
        oldFile.remove();
    }
}

void writeDoubleSourceFile()
{
    //Creating double file
    QFile doubleSourceFile("doubleSourceFile.txt");
    if(!doubleSourceFile.open(QIODevice::WriteOnly))
        return;
    QTextStream outTS(&doubleSourceFile);

    QRandomGenerator64 rd;
    for (int i = 0; i < 85000000; i++)
        outTS << rd.generateDouble() * std::numeric_limits<double>::max() << '\n';

    doubleSourceFile.close();

    //Creating serialized file
    if(!doubleSourceFile.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&doubleSourceFile);

    QFile file("file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);
    out.setVersion(QDataStream::Qt_5_12);

    while(!in.atEnd())
        out << in.readLine().toDouble();

    file.close();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QElapsedTimer timer;
    timer.start();
    writeDoubleSourceFile();
    qDebug() << "Finished writing doubleSourceFile.txt secs" << timer.elapsed()/1000;
    fileSorting("file.dat");
    qDebug() << "Finished sorting SortedFile.txt secs" << timer.elapsed()/1000;
    return a.exec();
}
