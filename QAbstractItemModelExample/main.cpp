#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractTableModel>
#include <QFile>
#include <QDebug>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    enum TableRoles
    {
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };

public:
    explicit TableModel(QObject *parent = nullptr)
    {
        idNamePhoneList_.append({"id", "name", "phone"});

        QFile dataFile("data.txt");
        dataFile.open(QIODevice::ReadOnly);
        QStringList tempStringList;

        while (!dataFile.atEnd())
        {
            tempStringList = QString(dataFile.readLine()).split("; ");
            qDebug() << tempStringList;
            idNamePhoneList_.append({tempStringList.at(0), tempStringList.at(1), tempStringList.at(2)});
            //        idNamePhoneList_.append({"0", "Max", "88005551234"});
        }
    }

    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
        return idNamePhoneList_.size();
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
        return idNamePhoneList_.at(0).size();
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        switch (role)
        {
        case TableDataRole:
        {
            return idNamePhoneList_.at(index.row()).at(index.column());
        };
        case HeadingRole:
        {
            if(index.row() == 0)
                return true;
            else
                return false;
        }

        }
        return QVariant();
    }
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles.insert(TableDataRole, "tabledata");
        roles.insert(HeadingRole, "heading");
        return roles;
    }
private:
    QList<QList<QString>> idNamePhoneList_;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

#include "main.moc"
