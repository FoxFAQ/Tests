#include <QCoreApplication>
#include <QRegExp>
#include <QDebug>

bool exactWildcard(const QString& mask, const QString& text)
{
    QRegExp rx(mask);
    rx.setPatternSyntax(QRegExp::Wildcard);
    return rx.exactMatch(text);
}

int wildcardPos(const QString& mask, const QString& text)
{
    QRegExp rx(mask);
    rx.setPatternSyntax(QRegExp::Wildcard);
    int pos = rx.indexIn(text);
    if(pos != -1)
        qDebug() << rx.cap();
    return pos;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Usually 1st function is used for the wildcard checks, just in case I made 2nd since it's not exactly specified
    qDebug() << exactWildcard("*.txt", "text.txt");//Exactly matches the wildcard
    qDebug() << wildcardPos("text.??", "abracadabra text.txt");//Finds substring based on wildcard

    return a.exec();
}
