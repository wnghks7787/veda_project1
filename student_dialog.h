/**
 * 유저 수정 등에 사용되는 dialog
 * 중복 검사 등을 할 수 있으며, 유저 정보 수정, 유저 추가 가능
 * 수정된 결과는 서버에 저장
 * */

#ifndef STUDENT_DIALOG_H
#define STUDENT_DIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QStringList>
#include <QPushButton>

class studentdialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief 함수 기능: 학생 정보 입력 대화 상자 생성 및 초기화
     * @param existingIds: 중복 검사를 위한 기존 학생 ID 목록
     * @param parent: 부모 위젯
     * @return: studentdialog 객체
     * @details 핵심 원리: QFormLayout을 기본 레이아웃으로 설정하고, ID 입력란에는 QHBoxLayout을 중첩하여 중복 확인 버튼을 배치함.
     */
    explicit studentdialog(const QStringList &existingIds, QWidget *parent = nullptr);

    /**
     * @brief 함수 기능: 입력된 이름 반환
     * @param: 없음
     * @return: 사용자가 입력한 이름(QString)
     */
    QString getName() const
    {
        return nameEdit->text();
    }

    /**
     * @brief 함수 기능: 입력된 전화번호 반환
     * @param: 없음
     * @return: 사용자가 입력한 전화번호(QString)
     */
    QString getPhone() const
    {
        return phoneEdit->text();
    }

    /**
     * @brief 함수 기능: 입력된 생년월일 반환
     * @param: 없음
     * @return: 사용자가 입력한 생년월일(QString)
     */
    QString getBirth() const
    {
        return birthEdit->text();
    }

    /**
     * @brief 함수 기능: 입력된 ID 반환
     * @param: 없음
     * @return: 사용자가 입력한 ID(QString)
     */
    QString getID() const
    {
        return idEdit->text();
    }

    /**
     * @brief 함수 기능: 입력된 비밀번호 반환
     * @param: 없음
     * @return: 사용자가 입력한 비밀번호(QString)
     */
    QString getPW() const
    {
        return pwEdit->text();
    }

    /**
     * @brief 함수 기능: 입력된 비고 내용 반환
     * @param: 없음
     * @return: 사용자가 입력한 비고 내용(QString)
     */
    QString getNote() const
    {
        return noteEdit->text();
    }

    /**
     * @brief 함수 기능: 수정 모드 시 기존 데이터를 입력창에 설정
     * @param name, phone, birth, id, pw, note: 설정할 기존 데이터들
     * @return: 없음
     * @details 핵심 원리: 전달받은 데이터를 각 QLineEdit에 채우고, ID 필드는 수정을 방지하기 위해 비활성화(setEnabled(false))함.
     */
    void setStudentData(const QString& name, const QString& phone, const QString& birth, const QString& id, const QString& pw, const QString& note);

private:
    QLineEdit *nameEdit, *phoneEdit, *ageEdit, *birthEdit, *idEdit, *pwEdit, *noteEdit;
    QStringList m_existingIds;
    bool m_isIdChecked = false; // 중복 확인 완료 여부
};
#endif // STUDENT_DIALOG_H