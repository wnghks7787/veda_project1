#ifndef SIGN_UP_MODULE_H
#define SIGN_UP_MODULE_H

#include <QString>
#include <QDate>

class SignUpModule
{
public:
    SignUpModule(QString name, QDate birthday, QString id, QString password, QString verify_password, QString phone_num);

    void createUser();
    bool verifyPassword();

private:
    QString name;
    QDate birthday;
    QString id;
    QString password;
    QString verify_password;
    QString phone_num;

    int calculateAge();
};

#endif // SIGN_UP_MODULE_H
