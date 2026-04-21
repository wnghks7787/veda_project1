#include "user_mainpage.h"
#include "./ui_user_mainpage.h"
#include "login.h"

UserMainpage::UserMainpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::user_page)
{
    ui->setupUi(this);
}

UserMainpage::~UserMainpage() {
    delete ui;
}
void UserMainpage::on_logout_button_clicked()
{
    msg_box = QMessageBox::critical(
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
    }
}

