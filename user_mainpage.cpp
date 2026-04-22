#include "user_mainpage.h"
#include "./ui_user_mainpage.h"
#include "login.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

UserMainpage::UserMainpage(Client* client, User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::user_page)
{
    ui->setupUi(this);

    this->client = client;
    this->user = user;

    setWindowTitle("출결 확인 시스템");
    resize(1100, 700);

    QWidget* sidebar = new QWidget();
    sidebar->setStyleSheet("background-coolor: #2c3e50");
    sidebar->setFixedWidth(200);


}

UserMainpage::~UserMainpage() {
    delete ui;
}

void UserMainpage::setId(QString &id)
{
    this->id = id;
}
/**
 * @brief 로그아웃 로직. 현 화면을 닫고 로귿인 페이지를 띄워준다.
 */
void UserMainpage::on_logout_button_clicked()
{
    msg_box = QMessageBox::information(
        this,
        "로그아웃",
        "로그아웃 하시겠습니까?",
        QMessageBox::Ok|
        QMessageBox::Cancel);



    if(msg_box == QMessageBox::Ok)
    {
        this->close();

        Login* login = new Login();
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();

        delete(user);
    }
}

/**
 * @brief 회원 탈퇴 로직
 */
void UserMainpage::on_withdraw_button_clicked()
{
    msg_box = QMessageBox::critical(
        this,
        "회원 탈퇴",
        "회원 탈퇴를 하시겠습니까?\n(주의! 취소할 수 없습니다.",
        QMessageBox::Ok|
        QMessageBox::Cancel);

    if(msg_box == QMessageBox::Ok)
    {
        QString id = user->getId();
        client->sendWithdraw(id);

        this->close();

        Login* login = new Login();
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();

        delete(user);
    }
}
