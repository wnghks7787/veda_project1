#include "user_mainpage.h"
#include "./ui_user_mainpage.h"

UserMainpage::UserMainpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

UserMainpage::~UserMainpage() {
    delete ui;
}