#ifndef USER_MAINPAGE_H
#define USER_MAINPAGE_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class user_page;
}
QT_END_NAMESPACE

class UserMainpage : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainpage(QWidget *parent = nullptr);
    ~UserMainpage() override;

private slots:
    void on_logout_button_clicked();

private:
    Ui::user_page *ui;

    QMessageBox::StandardButton msg_box;
};

#endif // USER_MAINPAGE_H
