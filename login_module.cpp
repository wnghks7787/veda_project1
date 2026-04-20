#include <QDebug>
#include "login_module.h"
#include "user_mainpage.h"

LoginModule::LoginModule(QString id, QString pw)
{
    this->id = id;
    this->pw = pw;
}

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
 * @brief LoginModule::login 로그인 로직. 상황에 따라 admin, user, 로그인실패로 연결한다.
 * @return admin 로그인 -> 1 반환 / user 로그인 -> 2 반환 / 로그인 실패 -> -1 반환
 */
int LoginModule::login()
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
    else
    {
        return -1;
    }
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