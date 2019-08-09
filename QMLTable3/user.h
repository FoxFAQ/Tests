#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVariant>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
public:
    User(QObject *parent = nullptr);
    User(const User &other);
    User(const QString &id, const QString &name, const QString &phone, QObject *parent = nullptr);

    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString phone() const;
    void setPhone(const QString &phone);
signals:
    void idChanged();
    void nameChanged();
    void phoneChanged();
private:
    QString id_;
    QString name_;
    QString phone_;
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
