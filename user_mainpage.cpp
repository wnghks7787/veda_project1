#include "user_mainpage.h"
#include "./ui_user_mainpage.h"

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
    qDebug() << "로그아웃";
}

