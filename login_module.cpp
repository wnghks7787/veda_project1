#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "login_module.h"
#include "user_mainpage.h"

/**
 * @author Joohwan Lim
 * @brief 로그인을 확인하는 부분
 * @param id 아이디
 * @param pw 비밀번호
 */
LoginModule::LoginModule(QString id, QString pw)
{
    this->id = id;
    this->pw = pw;
}
/**
 * @author Joohwan Lim
 * @brief 관리자인지 확인
 * @return ID가 "admin" 이면 true, 그렇지 않으면 false
 */
bool LoginModule::isAdmin()
{
    if(this->id == "admin")
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
 * @brief LoginModule::isUser
 * @return user(admin이 아닌 경우) true를 반환한다.
 */
bool LoginModule::isUser()
{
    return true;
}
/**
 * @author Joohwan Lim
 * @brief 로그인 로직. 상황에 따라 admin, user, 로그인실패로 연결한다.
 * @return admin 로그인 -> 1 반환 / user 로그인 -> 2 반환 / 로그인 실패 -> -1 반환
 */
int LoginModule::login()
{
    if(checkLoginValidate())
    {
        if(isAdmin())
        {
            loginWithAdmin();
            return 1;
        }
        else if(isUser())
        {
            loginWithUser();
            return 2;
        }
    }

    // 로그인 실패
    return -1;
}

void LoginModule::loginWithAdmin()
{
    qDebug() << "admin login";
}
void LoginModule::loginWithUser()
{
    qDebug() << "user login";
    UserMainpage* user_page = new UserMainpage();
    user_page->setAttribute(Qt::WA_DeleteOnClose);
    user_page->show();
}

QString LoginModule::getId()
{
    return this->id;
}

/**
 * @author Joohwan Lim
 * @brief 로그인을 할 수 있는지 확인하는 모듈
 * @return 로그인할 수 있으면 true, 아니면 false
 */
bool LoginModule::checkLoginValidate()
{
    QFile file("user.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "파일 열기 실패";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray users = doc.array();

    for(const QJsonValue &value : users)
    {
        QJsonObject user = value.toObject();

        QString json_id = user["id"].toString();
        QString json_pw = user["info"].toObject()["password"].toString();

        if(id == json_id && pw == json_pw)
        {
            return true;
        }
    }
    return false;
}