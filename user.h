#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

#include "client.h"

class User
{
public:
    User();
    User(QJsonObject user_json);
    ~User();

    QString getName() const;
    void setName(const QString &newName);
    QDate getBirthday() const;
    void setBirthday(const QDate &newBirthday);
    QString getId() const;
    void setId(const QString &newId);
    QString getPassword() const;
    void setPassword(const QString &newPassword);
    QString getPhone_num() const;
    void setPhone_num(const QString &newPhone_num);
    int getAge() const;
    void setAge(int newAge);

    int getPresent() const;
    int getAbsent() const;
    int getLate() const;
    int getEarly_leave() const;
    int getBe_out() const;

    QJsonObject getUserJson();

    void withdraw();

private:
    QString name;
    QDate birthday;
    QString id;
    QString password;
    QString phone_num;
    int age;
    int present;
    int absent;
    int late;
    int early_leave;
    int be_out;

    Client* client;
};

#endif // USER_H
