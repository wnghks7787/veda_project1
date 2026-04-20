#include "user.h"

User::User() {}

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

int User::getAttendance() const
{
    return attendance;
}

void User::setAttendance(int newAttendance)
{
    attendance = newAttendance;
}

int User::getAbsent() const
{
    return absent;
}

void User::setAbsent(int newAbsent)
{
    absent = newAbsent;
}

int User::getLate() const
{
    return late;
}

void User::setLate(int newLate)
{
    late = newLate;
}

int User::getEarly_leave() const
{
    return early_leave;
}

void User::setEarly_leave(int newEarly_leave)
{
    early_leave = newEarly_leave;
}

int User::getBe_out() const
{
    return be_out;
}

void User::setBe_out(int newBe_out)
{
    be_out = newBe_out;
}