#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QStringList>
#include <QPushButton>

class AddStudentDialog : public QDialog
{
    Q_OBJECT
public:
    // 기존 ID 목록을 인자로 받는 생성자
    explicit AddStudentDialog(const QStringList &existingIds, QWidget *parent = nullptr);

    QString getName() const { return nameEdit->text(); }
    QString getPhone() const { return phoneEdit->text(); }
    //QString getAge() const { return ageEdit->text(); }
    QString getBirth() const { return birthEdit->text(); }
    QString getID() const { return idEdit->text(); }
    QString getPW() const { return pwEdit->text(); }
    QString getNote() const { return noteEdit->text(); }

private:
    QLineEdit *nameEdit, *phoneEdit, *ageEdit, *birthEdit, *idEdit, *pwEdit, *noteEdit;
    QStringList m_existingIds;
    bool m_isIdChecked = false; // 중복 확인 완료 여부
};
#endif