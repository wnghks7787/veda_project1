#ifndef USER_MAINPAGE_H
#define USER_MAINPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class UserMainpage : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainpage(QWidget *parent = nullptr);
    ~UserMainpage() override;

private:
    Ui::Widget *ui;
};

#endif // USER_MAINPAGE_H
