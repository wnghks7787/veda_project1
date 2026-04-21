#include "sign_up_module.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/**
 * @brief 사용자 정보 입력
 * @param name
 * @param birthday
 * @param id
 * @param password
 * @param phone_num
 */
SignUpModule::SignUpModule(QString name, QDate birthday, QString id, QString password, QString verify_password, QString phone_num)
{
    this->name = name;
    this->birthday = birthday;
    this->id = id;
    this->password = password;
    this->verify_password = verify_password;
    this->phone_num = phone_num;
}

/**
 * @author Joohwan Lim
 * @brief User Json 파일 생성
 */
void SignUpModule::createUser()
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

    // 사용자 추가
    QJsonObject obj;
    obj["id"]=  id;

    QJsonObject infoObj;
    infoObj["name"] = name;
    infoObj["birthday"] = birthday.toString("yyyy-MM-dd");
    infoObj["password"] = password;
    infoObj["phone_num"] = phone_num;
    infoObj["age"] = calculateAge();

    obj["info"] = infoObj;


    QJsonObject attendanceObj;
    attendanceObj["present"] = 0;
    attendanceObj["late"] = 0;
    attendanceObj["early_leave"] = 0;
    attendanceObj["be_out"] = 0;

    obj["attendance"] = attendanceObj;

    users.append(obj);


    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(users).toJson(QJsonDocument::Indented));
        file.close();
    }
}

bool SignUpModule::verifyPassword()
{
    if(password == verify_password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @author Joohwan Lim
 * @brief 한국식 나이를 계산
 * @return 계산된 한국 나이
 */
int SignUpModule::calculateAge()
{
    QDate today = QDate::currentDate();
    return today.year() - birthday.year() + 1;
}