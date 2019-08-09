#include "user.h"

User::User(QObject *parent)
    : QObject {parent},
      id_ {""},
      name_ {""},
      phone_ {""}
{

}

User::User(const User &other)
    : QObject {other.parent()},
      id_ {other.id()},
      name_ {other.id()},
      phone_ {other.phone()}
{

}

User::User(const QString &id, const QString &name, const QString &phone, QObject *parent)
    : QObject {parent},
      id_ {id},
      name_ {name},
      phone_ {phone}
{

}

QString User::id() const
{
    return id_;
}

void User::setId(const QString &id)
{
    id_ = id;
    emit idChanged();
}

QString User::name() const
{
    return name_;
}

void User::setName(const QString &name)
{
    name_ = name;
    emit nameChanged();
}

QString User::phone() const
{
    return phone_;
}

void User::setPhone(const QString &phone)
{
    phone_ = phone;
    emit phoneChanged();
}
