#include "user_mainpage.h"
#include "./ui_user_mainpage.h"

#include "login.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

UserMainpage::UserMainpage(Client* client, User* user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    this->client = client;
    this->user = user;

    setWindowTitle("출결 확인 시스템"); // 타이틀 지정

    // 출결 현황 값 지정
    int present = user->getPresent(); // 출석
    int late = user->getLate(); // 지각
    int early = user->getEarlyLeave(); // 조퇴
    int out = user->getBeOut(); // 외출
    int abs = user->getAbsent(); // 결석

    // 지각/조퇴/외출 3회당 결석 1회
    int effectivAabsent = abs + (late + early + out) / 3;
    double absentRate = effectivAabsent;
    double attendanceRate = 100.0 - effectivAabsent;

    // ui에 결과 출력
    ui->label_title->setText(QString("<h2>%1님의 출결 현황 (총 100일)</h2>").arg(user->getName()));
    ui->label_present->setText(QString("출석: %1회").arg(present));
    ui->label_late->setText(QString("지각: %1회").arg(late));
    ui->label_early->setText(QString("조퇴: %1회").arg(early));
    ui->label_out->setText(QString("외출: %1회").arg(out));
    ui->label_absent->setText(QString("결석: %1회").arg(abs));
    ui->label_rate->setText(QString("출석률: %1% / 결석률: %2%").arg(attendanceRate, 0, 'f', 1).arg(absentRate, 0, 'f', 1));
}

UserMainpage::~UserMainpage() {
    delete ui;
}

void UserMainpage::setId(QString &id)
{
    this->id = id;
}
/**
 * @brief 로그아웃 로직. 현 화면을 닫고 로귿인 페이지를 띄워준다.
 */
void UserMainpage::on_logout_button_clicked()
{
    msgBox = QMessageBox::information(
        this,
        "로그아웃",
        "로그아웃 하시겠습니까?",
        QMessageBox::Ok|
        QMessageBox::Cancel);



    if(msgBox == QMessageBox::Ok)
    {
        this->close();

        Login* login = new Login();
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();

        delete(user);
    }
}

/**
 * @brief 회원 탈퇴 로직
 */
void UserMainpage::on_withdraw_button_clicked()
{
    msgBox = QMessageBox::critical(
        this,
        "회원 탈퇴",
        "회원 탈퇴를 하시겠습니까?\n(주의! 취소할 수 없습니다.",
        QMessageBox::Ok|
        QMessageBox::Cancel);

    if(msgBox == QMessageBox::Ok)
    {
        QString id = user->getId();
        client->sendWithdraw(id);

        this->close();

        Login* login = new Login();
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();

        delete(user);
    }
}
