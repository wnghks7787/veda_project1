#include "user.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

User::User() {}
User::User(QString id)
{
    QFile file("user.json");
    QJsonArray users;

    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);

        if(doc.isArray())
        {
            users = doc.array();
        }
    }
    QJsonObject obj;

    for(const QJsonValue &value : users)
    {
        QJsonObject json_user = value.toObject();

        QString json_id = json_user["id"].toString();

        if(id == json_id)
        {
            QJsonObject json_info = json_user["info"].toObject();
            this->id = json_id;
            this->name = json_info["name"].toString();
            this->password = json_info["password"].toString();
            this->birthday = QDate::fromString(json_user["birthday"].toString());
            this->phone_num = json_info["phone_num"].toString();
            this->age = json_info["age"].toInt();

            QJsonObject json_attendance = json_user["attendance"].toObject();
            this->present = json_attendance["present"].toInt();
            this->absent = json_attendance["absent"].toInt();
            this->late = json_attendance["late"].toInt();
            this->early_leave = json_attendance["early_leave"].toInt();
            this->be_out = json_attendance["be_out"].toInt();

            break;
        }
    }
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

bool User::withdraw()
{
    QFile file("user.json");

    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if(!doc.isArray())
    {
        return false;
    }

    QJsonArray arr = doc.array();

    for(int i = 0 ; i < arr.size() ; i++)
    {
        QJsonObject obj = arr[i].toObject();

        if(obj["id"] == id)
        {
            arr.removeAt(i);
            break;
        }
    }

    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
    file.close();

    return true;
}