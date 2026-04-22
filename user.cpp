#include "user.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

User::User() {}
// 생성 시 유저 정보를 저장
User::User(QJsonObject user_json)
{
    QJsonObject info = user_json["info"].toObject();
    this->name = info["name"].toString();
    this->birthday = QDate::fromString(info["birthday"].toString());
    this->id = user_json["id"].toString();
    this->password = info["password"].toString();
    this->phoneNum = info["phoneNum"].toString();
    this->age = info["age"].toInt();

    QJsonObject attendance = user_json["attendance"].toObject();
    this->present = attendance["present"].toInt();
    this->absent = attendance["absent"].toInt();
    this->late = attendance["late"].toInt();
    this->earlyLeave = attendance["earlyLeave"].toInt();
    this->beOut = attendance["beOut"].toInt();
}

User::~User()
{

}
//
// 이하 getter setter
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

QString User::getPhoneNum() const
{
    return phoneNum;
}

void User::setPhoneNum(const QString &newPhoneNum)
{
    phoneNum = newPhoneNum;
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

int User::getEarlyLeave() const
{
    return earlyLeave;
}

int User::getBeOut() const
{
    return beOut;
}

QJsonObject User::getUserJson()
{
    QJsonObject res;

    QJsonObject info = res["info"].toObject();
    info["name"] = name;
    info["birthday"] = birthday.toString();
    info["password"] = password;
    info["phoneNum"] = phoneNum;
    info["age"] = age;

    QJsonObject attendance = res["attendance"].toObject();
    attendance["present"] = present;
    attendance["absent"] = absent;
    attendance["late"] = late;
    attendance["earlyLeave"] = earlyLeave;
    attendance["beOut"] = beOut;

    res["info"] = info;
    res["attendance"] = attendance;
    res["id"] = id;

    return res;
}