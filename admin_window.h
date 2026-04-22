#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QWidget>
#include <QString>
#include <QHeaderView>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>


class QTableWidget;
class QPushButton;

/**
 * @brief 고객 정보를 저장하고 전달하기 위한 데이터 구조체입니다.
 */
struct CustomerData {
    QString name;   ///< 고객 이름
    QString phone;  ///< 연락처
    QString age;    ///< 나이
    QString grade;  ///< 고객 등급
};

/**
 * @class admin_window
 * @brief 100% C++ 코드로 구성된 고객 정보 관리 윈도우 클래스입니다.
 */
class admin_window : public QWidget
{
    Q_OBJECT

public:
    explicit admin_window(QWidget *parent = nullptr);
    ~admin_window();

private slots:
    void on_pushButton_2_clicked();


private:
    Ui::Widget *ui;
    void setupUI();
    void addRowToTable(const CustomerData& data);
    bool validateInput(const QString& name, const QString& phone, const QString& ageStr, const QString& grade);


    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *ageEdit;
    QLineEdit *gradeEdit;

};

#endif // ADMIN_WINDOW_H