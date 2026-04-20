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

private:
    Ui::sign_up_dialog* ui;
};

#endif // SIGN_UP_H
