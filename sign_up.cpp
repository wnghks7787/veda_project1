#include "sign_up.h"
#include "./ui_sign_up.h"

#include "sign_up_module.h"

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sign_up_dialog)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}
void SignUp::on_buttonBox_accepted()
{
    // 처리 로직
    SignUpModule sign_up_module(
        ui->name_edit->text(),
        ui->birthday_edit->date(),
        ui->id_edit->text(), ui->pw_edit->text(),
        ui->verify_pw_edit->text(),
        ui->phone_edit->text()
    );

    sign_up_module.createUser();
}

