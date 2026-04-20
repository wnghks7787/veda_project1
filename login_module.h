#ifndef LOGIN_MODULE_H
#define LOGIN_MODULE_H

#include <QString>

class LoginModule
{
public:
    LoginModule(QString id, QString pw);

    bool isAdmin();

    void loginWithAdmin();
    void loginWithUser();

    QString getId();

private:
    QString id;
    QString pw;

    bool admin;
};

#endif // LOGIN_MODULE_H
