#include "user_mainpage.h"
#include "./ui_user_mainpage.h"
#include "login.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

UserMainpage::UserMainpage(User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::user_page)
{
    ui->setupUi(this);
}

UserMainpage::~UserMainpage() {
    delete ui;
}

void UserMainpage::setId(QString &id)
{
    this->id = id;
}

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


// void UserMainpage::on_withdraw_button_clicked()
// {
//     msg_box = QMessageBox::critical(
//         this,
//         "회원 탈퇴",
//         "회원 탈퇴를 하시겠습니까?\n(주의! 취소할 수 없습니다.",
//         QMessageBox::Ok|
//         QMessageBox::Cancel);

//     if(msg_box == QMessageBox::Ok)
//     {
//         if(user->withdraw())
//         {
//             this->close();

//             Login* login = new Login();
//             login->setAttribute(Qt::WA_DeleteOnClose);
//             login->show();
//         }
//         else
//         {
//             qDebug() << "탈퇴 실패";
//         }
//     }
// }
