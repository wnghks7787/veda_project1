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
    this->phone_num = phone_num;
    // this->attendance = 0;
    // this->absent = 0;
    // this->late = 0;
    // this->early_leave = 0;
    // this->be_out = 0;
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
    obj["name"] = name;
    obj["birthday"] = birthday.toString("yyyy-MM-dd");
    obj["password"] = password;
    obj["phone_num"] = phone_num;
    obj["age"] = calculateAge();
    obj["attendance"] = 0;
    obj["late"] = 0;
    obj["early_leave"] = 0;
    obj["be_out"] = 0;

    users.append(obj);


    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(users).toJson(QJsonDocument::Indented));
        file.close();
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
