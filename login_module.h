#ifndef LOGIN_MODULE_H
#define LOGIN_MODULE_H

#include <QString>
#include <QMessageBox>

class LoginModule
{
public:
    LoginModule(QString id, QString pw);

    bool isAdmin();
    bool isUser();

    int login();

    QString getId();
    QString getName();

private:
    QString id;
    QString pw;
    QString name;
    QMessageBox::StandardButton msg_box;

    void loginWithAdmin();
    void loginWithUser();

    bool checkLoginValidate();
};

#endif // LOGIN_MODULE_H
