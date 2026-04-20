#ifndef USER_MAINPAGE_H
#define USER_MAINPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPage;
}
QT_END_NAMESPACE

class UserMainpage : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainpage(QWidget *parent = nullptr);
    ~UserMainpage() override;

private:
    Ui::MainPage *ui;
};

#endif // USER_MAINPAGE_H
