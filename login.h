#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include <QJsonObject>
#include "user_mainpage.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

private slots:
    void on_login_button_clicked();

    void on_sign_up_button_clicked();
    void onLoginResult(bool success, QJsonObject user_json);

private:
    QMessageBox::StandardButton msg_box;

    UserMainpage* user_page;
    Ui::Widget *ui;

    Client* client;
};
#endif // LOGIN_H
