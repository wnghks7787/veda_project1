#include "login.h"
#include "./ui_login.h"
#include "user_mainpage.h"

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
    user_page = new UserMainpage();
    user_page->setAttribute(Qt::WA_DeleteOnClose);
    user_page->show();

    this->close();
}

