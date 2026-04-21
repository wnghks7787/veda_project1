#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "user_mainpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

private slots:
    void on_login_button_clicked();

    void on_sign_up_button_clicked();

private:
    UserMainpage* user_page =  new UserMainpage();
    Ui::Widget *ui;
};
#endif // LOGIN_H
