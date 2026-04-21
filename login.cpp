#include "login.h"
#include "./ui_login.h"
#include "sign_up.h"

#include <QMessageBox>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    client = new Client(this);
    client->connectToServer();

    connect(client, SIGNAL(loginResult(bool, QString)), this, SLOT(onLoginResult(bool, QString)));
}

Login::~Login() {
    delete ui;
}
void Login::on_login_button_clicked()
{
    QString id, pw;
    id = ui->id_line->text();
    pw = ui->pw_line->text();

    client->sendLogin(id, pw);
}

void Login::onLoginResult(bool success, QString msg)
{
    if(success)
    {
        qDebug() << "success";
    }
    else
    {
        qDebug() << "fail";
    }
}


void Login::on_sign_up_button_clicked()
{
    SignUp* sign_up_page = new SignUp();
    sign_up_page->setAttribute(Qt::WA_DeleteOnClose);
    sign_up_page->show();
}

