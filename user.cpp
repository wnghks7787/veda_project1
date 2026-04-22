#include "user.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

User::User() {}
User::User(QJsonObject user_json)
{
    QJsonObject info = user_json["info"].toObject();
    this->name = info["name"].toString();
    this->birthday = QDate::fromString(info["birthday"].toString());
    this->id = user_json["id"].toString();
    this->password = info["password"].toString();
    this->phone_num = info["phone_num"].toString();
    this->age = info["age"].toInt();

    QJsonObject attendance = user_json["attendance"].toObject();
    this->present = attendance["present"].toInt();
    this->absent = attendance["absent"].toInt();
    this->late = attendance["late"].toInt();
    this->early_leave = attendance["early_leave"].toInt();
    this->be_out = attendance["be_out"].toInt();
}

User::~User()
{

}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}

QDate User::getBirthday() const
{
    return birthday;
}

void User::setBirthday(const QDate &newBirthday)
{
    birthday = newBirthday;
}

QString User::getId() const
{
    return id;
}

void User::setId(const QString &newId)
{
    id = newId;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    password = newPassword;
}

QString User::getPhone_num() const
{
    return phone_num;
}

void User::setPhone_num(const QString &newPhone_num)
{
    phone_num = newPhone_num;
}

int User::getAge() const
{
    return age;
}

void User::setAge(int newAge)
{
    age = newAge;
}

int User::getPresent() const
{
    return present;
}

int User::getAbsent() const
{
    return absent;
}

int User::getLate() const
{
    return late;
}

int User::getEarly_leave() const
{
    return early_leave;
}

int User::getBe_out() const
{
    return be_out;
}

QJsonObject User::getUserJson()
{
    QJsonObject res;

    QJsonObject info = res["info"].toObject();
    info["name"] = name;
    info["birthday"] = birthday.toString();
    info["password"] = password;
    info["phone_num"] = phone_num;
    info["age"] = age;

    QJsonObject attendance = res["attendance"].toObject();
    attendance["present"] = present;
    attendance["absent"] = absent;
    attendance["late"] = late;
    attendance["early_leave"] = early_leave;
    attendance["be_out"] = be_out;

    res["info"] = info;
    res["attendance"] = attendance;
    res["id"] = id;

    return res;
}