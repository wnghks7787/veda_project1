#ifndef LOGIN_MODULE_H
#define LOGIN_MODULE_H

#include <QString>

class LoginModule
{
public:
    LoginModule(QString id, QString pw);

    bool isAdmin();
    bool isUser();

    int login();

    QString getId();

private:
    QString id;
    QString pw;

    void loginWithAdmin();
    void loginWithUser();
};

#endif // LOGIN_MODULE_H
