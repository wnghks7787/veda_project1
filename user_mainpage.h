/**
 * 유저로 로그인했을 때 볼 수 있는 화면
 * user_mainpage.ui 를 통해 유저 페이지 생성
 * 로그인 시 받은 정보를 통해 자신의 출결 현황을 조회할 수 있음
 * 로그아웃, 회원탈퇴 가능
 * */

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

/**
 * @brief 유저 메인윈도우 클래스
 */
class UserMainpage : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainpage(Client* client, User* user, QWidget *parent = nullptr);
    ~UserMainpage() override;

    void setId(QString &id);

private slots:
    void on_logout_button_clicked(); // 로그아웃 버튼 작동 슬롯
    void on_withdraw_button_clicked(); // 회원탈퇴 버튼 작동 슬롯

private:
    Ui::user_page *ui;

    QString id; // 로그인 한 유저의 아이디
    QMessageBox::StandardButton msg_box; // 메시지 박스
    User* user; // 로그인 한 유저의 정보
    Client* client; // 클라이언트 소켓
};

#endif // USER_MAINPAGE_H
