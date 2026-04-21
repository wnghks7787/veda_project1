#include "sign_up.h"
#include "./ui_sign_up.h"

#include "sign_up_module.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QMessageBox>

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sign_up_dialog)
{
    ui->setupUi(this);

    verified_id = false;
}

SignUp::~SignUp()
{
    delete ui;
}
void SignUp::on_ok_button_clicked()
{
    // 처리 로직
    SignUpModule sign_up_module(
        ui->name_edit->text(),
        ui->birthday_edit->date(),
        ui->id_edit->text(), ui->pw_edit->text(),
        ui->verify_pw_edit->text(),
        ui->phone_edit->text()
    );

    if(sign_up_module.verifyPassword() && verified_id)
    {
        sign_up_module.createUser();
        this->close();
    }
    else if(!verified_id)
    {
        reply = QMessageBox::critical(
            this,
            "회원가입 실패",
            "중복 확인을 해야 합니다.",
            QMessageBox::Ok);
    }
    else
    {
        reply = QMessageBox::critical(
            this,
            "회원가입 실패",
            "비밀번호가 다릅니다.",
            QMessageBox::Ok);
    }
}


void SignUp::on_verify_id_button_clicked()
{
    QFile file("user.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "파일 열기 실패";
    }

    QByteArray data = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray users = doc.array();

    bool id_check_ok = false;
    for(const QJsonValue &value : users)
    {
        QJsonObject user = value.toObject();

        QString json_id = user["id"].toString();

        if(ui->id_edit->text() == json_id)
        {
            verified_id = false;
            id_check_ok = true;
            reply = QMessageBox::critical(
                this,
                "중복 검사",
                "아이디가 이미 존재합니다.",
                QMessageBox::Ok);
            break;
        }
    }

    if(!id_check_ok)
    {
        verified_id = true;

        reply = QMessageBox::information(
            this,
            "중복 검사",
            "사용 가능한 아이디입니다.",
            QMessageBox::Ok);
    }
}


void SignUp::on_id_edit_textChanged(const QString &arg1)
{
    verified_id = false;
}


void SignUp::on_cancel_button_clicked()
{
    this->close();
}

