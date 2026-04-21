#include "login.h"
#include "./ui_login.h"
#include "login_module.h"
#include "sign_up.h"

#include <QMessageBox>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}
void Login::on_login_button_clicked()
{
    QString id, pw;
    id = ui->id_line->text();
    pw = ui->pw_line->text();

    LoginModule login_module(id, pw);

    int success = login_module.login();

    if(success == -1)
    {
        return;
    }
    else
    {
        this->close();
    }
}


void Login::on_sign_up_button_clicked()
{
    SignUp* sign_up_page = new SignUp();
    sign_up_page->setAttribute(Qt::WA_DeleteOnClose);
    sign_up_page->show();
}

