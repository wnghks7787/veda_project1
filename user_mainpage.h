#ifndef USER_MAINPAGE_H
#define USER_MAINPAGE_H

#include <QWidget>
#include <QMessageBox>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class user_page;
}
QT_END_NAMESPACE

class UserMainpage : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainpage(Client* client, User* user, QWidget *parent = nullptr);
    ~UserMainpage() override;

    void setId(QString &id);

private slots:
    void on_logout_button_clicked();

    void on_withdraw_button_clicked();

private:
    Ui::user_page *ui;

    QString id;
    QMessageBox::StandardButton msg_box;
    User* user;
    Client* client;
};

#endif // USER_MAINPAGE_H
