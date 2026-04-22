#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class sign_up_dialog;
}
QT_END_NAMESPACE

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(Client* client, QWidget *parent = nullptr);
    ~SignUp() override;

private slots:
    void on_verify_id_button_clicked();

    void on_id_edit_textChanged(const QString &arg1);

    void on_ok_button_clicked();

    void on_cancel_button_clicked();

    void onVerifiedResult(bool success);

    void onSignUpResult(bool success);

private:
    Ui::sign_up_dialog* ui;

    bool verified_id; // id 중복 확인
    QMessageBox::StandardButton reply; // 메시지 박스
    Client* client; // 클라이언트 소켓
};

#endif // SIGN_UP_H
