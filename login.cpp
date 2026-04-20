#include "login.h"
#include "./ui_login.h"
#include "user_mainpage.h"
#include "login_module.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}
void Login::on_pushButton_clicked()
{
    QString id, pw;
    id = ui->lineEdit_2->text();
    pw = ui->lineEdit->text();

    LoginModule login_module(id, pw);

    int success = login_module.login();

    if(success == -1)
    {
        qDebug()<< "로그인 실패";
    }
    else if(success == 1)
    {
        qDebug() << "관리자 로그인";
        this->close();
    }
    else if(success == 2)
    {
        qDebug() << "유저 로그인";
        this->close();
    }
    // user_page = new UserMainpage();
    // user_page->setAttribute(Qt::WA_DeleteOnClose);
    // user_page->show();

    // this->close();
}

