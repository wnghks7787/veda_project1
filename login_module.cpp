#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

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
    msg_box = QMessageBox::critical(
        nullptr,
        "로그인 실패",
        "로그인에 실패하였습니다.\n아이디와 비밀번호를 확인하세요.",
        QMessageBox::Ok);

    return -1;
}
/**
 * @author Joohwan Lim
 * @brief 관리자 로그인
 */
void LoginModule::loginWithAdmin()
{
    qDebug() << "admin login";
}
/**
 * @author Joohwan Lim
 * @brief 유저 로그인
 */
void LoginModule::loginWithUser()
{
    msg_box = QMessageBox::information(
        nullptr,
        "로그인 성공",
        QString("%1님 환영합니다.").arg(name),
        QMessageBox::Ok);

    UserMainpage* user_page = new UserMainpage(id);
    user_page->setAttribute(Qt::WA_DeleteOnClose);
    user_page->show();
}

QString LoginModule::getId()
{
    return this->id;
}

QString LoginModule::getName()
{
    return this->name;
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
            this->name = user["info"].toObject()["name"].toString();
            return true;
        }
    }
    return false;
}