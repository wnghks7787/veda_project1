#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

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

private:
    Ui::Widget *ui;
};
#endif // LOGIN_H
