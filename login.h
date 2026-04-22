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
    void onLoginResultAdmin(bool success, QJsonObject user_json, QJsonArray users_info);

private:
    QMessageBox::StandardButton msg_box; // 메시지 박스

    UserMainpage* user_page; // 유저 페이지
    Ui::Widget *ui;

    Client* client; // 클라이언트 소켓
};
#endif // LOGIN_H
