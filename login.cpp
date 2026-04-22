#include "login.h"
#include "./ui_login.h"
#include "sign_up.h"
#include "adminwindow.h"
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

/**
 * @brief 로그인 버튼 선택 시
 */
void Login::on_login_button_clicked()
{
    QString id, pw;
    id = ui->id_line->text();
    pw = ui->pw_line->text();

    client->sendLogin(id, pw);
}

/**
 * @brief 로그인 성공 여부 받아오기
 * @param success 성공/실패 여부
 * @param user_json 유저 데이터. 실패 시, empty 객체 받아옴
 */
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
        if(user->getId() == "admin")
        {
            Adminwindow* admin_page = new Adminwindow();
            admin_page->setAttribute(Qt::WA_DeleteOnClose);
            admin_page->show();
        }
        else
        {
            UserMainpage* user_page = new UserMainpage(client, user);
            user_page->setAttribute(Qt::WA_DeleteOnClose);
            user_page->show();
        }


        this->close();
    }
    else
    {
        qDebug() << "fail";
    }
}

/**
 * @brief 회원가입 버튼 선택 시
 */
void Login::on_sign_up_button_clicked()
{
    SignUp* sign_up_page = new SignUp(client);
    sign_up_page->setAttribute(Qt::WA_DeleteOnClose);
    sign_up_page->show();
}

