#include "login_module.h"

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

void LoginModule::loginWithAdmin()
{

}
void LoginModule::loginWithUser()
{

}

QString LoginModule::getId()
{
    return this->id;
}