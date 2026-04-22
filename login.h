/**
 * 로그인 로직을 처리하는 클래스
 * login.ui를 통해 로그인 페이지를 생성
 * 로그인 시 서버와 통신하며, 아이디/비밀번호 정보를 서버에 전송
 * 회원가입 시 회원가입 페이지를 띄워주는 역할을 수행
 * */

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
    void on_login_button_clicked(); // 로그인 버튼 작동 슬롯

    void on_sign_up_button_clicked(); // 회원가입 버튼 작동 슬롯
    void onLoginResult(bool success, QJsonObject userJson); // 서버로부터 로그인 결과 수신(비관리자)
    void onLoginResultAdmin(bool success, QJsonObject userJson, QJsonArray usersInfo); // 서버로부터 로그인 결과 수신(관리자)

private:
    QMessageBox::StandardButton msg_box; // 메시지 박스

    UserMainpage* userPage; // 유저 페이지
    Ui::Widget *ui;

    Client* client; // 서버와 통신할 클라이언트 객체
};
#endif // LOGIN_H
