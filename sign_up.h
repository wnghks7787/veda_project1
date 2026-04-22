/**
 * 회원가입 로직을 처리하는 클래스
 * sign_up.ui를 통해 회원가입 페이지를 생성
 * 회원가입 시 서버와 통신하며, 이름, 아이디, 비밀번호, 생년월일, 전화번호를 서버에 전송
 * 아이디 중복확인, 비밀번호 확인 로직 구현
 * */

#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class sign_up_dialog;
}
QT_END_NAMESPACE

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(Client* client, QWidget *parent = nullptr);
    ~SignUp() override;

private slots:
    void on_verify_id_button_clicked(); // 아이디 중복확인 슬롯
    void on_id_edit_textChanged(const QString &arg1); // 아이디 필드 변경 시 작동 슬롯
    void on_ok_button_clicked(); // 회원가입 버튼 슬롯
    void on_cancel_button_clicked(); // 취소버튼 슬롯
    void onVerifiedResult(bool success);// 서버로부터 아이디 중복확인 결과 수신
    void onSignUpResult(bool success); // 서버로부터 회원가입 결과 수신

private:
    Ui::sign_up_dialog* ui;

    bool verified_id; // id 중복 확인
    QMessageBox::StandardButton reply; // 메시지 박스
    Client* client; // 서버와 통신할 클라이언트 객체
};

#endif // SIGN_UP_H
