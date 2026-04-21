#include "sign_up.h"
#include "./ui_sign_up.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QMessageBox>

SignUp::SignUp(Client* client, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sign_up_dialog)
{
    ui->setupUi(this);

    verified_id = false;
    this->client = client;

    connect(client, SIGNAL(verifiedResult(bool)), this, SLOT(onVerifiedResult(bool)));
    connect(client, SIGNAL(signUpResult(bool)), this, SLOT(onSignUpResult(bool)));
}

SignUp::~SignUp()
{
    delete ui;
}
void SignUp::on_ok_button_clicked()
{
    // 실패 로직
    if(!verified_id)
    {
        reply = QMessageBox::critical(
            this,
            "회원가입 실패",
            "중복 확인을 해야 합니다.",
            QMessageBox::Ok);
        return;
    }
    if(ui->pw_edit->text() != ui->verify_pw_edit->text())
    {
        reply = QMessageBox::critical(
            this,
            "회원가입 실패",
            "비밀번호가 다릅니다.",
            QMessageBox::Ok);
        return;
    }


    // 성공 로직
    QJsonObject user;
    user["name"] = ui->name_edit->text();
    user["birthdya"] = ui->birthday_edit->text();
    user["id"] = ui->id_edit->text();
    user["password"] = ui->pw_edit->text();
    user["phone_num"] = ui->phone_edit->text();

    client->sendSignUp(user);
}


void SignUp::on_verify_id_button_clicked()
{
    QString id;
    id = ui->id_edit->text();

    client->sendVerifyId(id);
}

void SignUp::onVerifiedResult(bool success)
{
    if(success)
    {
        verified_id = true;
        reply = QMessageBox::information(
            this,
            "중복 검사",
            "사용 가능한 아이디입니다.",
            QMessageBox::Ok);
    }
    else
    {
        verified_id = false;
        reply = QMessageBox::critical(
            this,
            "중복 검사",
            "아이디가 이미 존재합니다.",
            QMessageBox::Ok);
    }
}

void SignUp::onSignUpResult(bool success)
{
    qDebug() << success;
    if(success)
    {
        reply = QMessageBox::information(
            this,
            "회원 가입",
            "회원 가입에 성공하였습니다.",
            QMessageBox::Ok);
    }
    this->close();
}

void SignUp::on_id_edit_textChanged(const QString &arg1)
{
    verified_id = false;
}


void SignUp::on_cancel_button_clicked()
{
    this->close();
}

