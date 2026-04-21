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

    connect(client, SIGNAL(loginResult(bool, QJsonObject)), this, SLOT(onLoginResult(bool, QJsonObject)));
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

void Login::onLoginResult(bool success, QJsonObject user_json)
{
    if(success)
    {
        qDebug() << "success";

        User* user = new User(user_json);

        msg_box = QMessageBox::information(
            this,
            "로그인 성공",
            QString("%1님 환영합니다.").arg(user->getName()),
            QMessageBox::Ok);

        UserMainpage* user_page = new UserMainpage(client, user);
        user_page->setAttribute(Qt::WA_DeleteOnClose);
        user_page->show();

        this->close();
    }
    else
    {
        qDebug() << "fail";
    }
}


void Login::on_sign_up_button_clicked()
{
    SignUp* sign_up_page = new SignUp(client);
    sign_up_page->setAttribute(Qt::WA_DeleteOnClose);
    sign_up_page->show();
}

