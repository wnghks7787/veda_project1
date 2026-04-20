#include "sign_up.h"
#include "./ui_sign_up.h"

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