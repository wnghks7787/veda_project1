#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class sign_up_dialog;
}
QT_END_NAMESPACE

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp() override;

private slots:
    void on_verify_id_button_clicked();

    void on_id_edit_textChanged(const QString &arg1);

    void on_ok_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::sign_up_dialog* ui;

    bool verified_id;
    QMessageBox::StandardButton reply;
};

#endif // SIGN_UP_H
