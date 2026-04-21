#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>

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
    void on_buttonBox_accepted();

    void on_verify_id_button_clicked();

    void on_id_edit_textChanged(const QString &arg1);

private:
    Ui::sign_up_dialog* ui;

    bool verified_id;
};

#endif // SIGN_UP_H
