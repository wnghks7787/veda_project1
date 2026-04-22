#include "student_dialog.h"
#include <QMessageBox>
#include <QHBoxLayout>

/**
 * @brief 함수 기능: 생성자 및 초기 UI 설정
 * @param existingIds: 중복 검사용 ID 리스트
 * @param parent: 부모 위젯
 * @return: 없음 (생성자)
 */
StudentDialog::StudentDialog(const QStringList &existingIds, QWidget *parent)
    : QDialog(parent), m_existingIds(existingIds)
{
    setWindowTitle("학생 정보 추가");

    // [핵심 원리]: QFormLayout을 사용하여 '라벨: 입력창' 형태의 수직 구조를 잡음.
    QFormLayout *form = new QFormLayout(this);

    nameEdit = new QLineEdit();
    phoneEdit = new QLineEdit();
    birthEdit = new QLineEdit();

    // [핵심 원리]: ID 입력 부분은 별도의 QHBoxLayout을 만들어 버튼과 가로로 나란히 배치함.
    idEdit = new QLineEdit();
    QPushButton *btnCheck = new QPushButton("중복 확인");
    QHBoxLayout *idLayout = new QHBoxLayout();
    idLayout->addWidget(idEdit);
    idLayout->addWidget(btnCheck);

    pwEdit = new QLineEdit();
    pwEdit->setEchoMode(QLineEdit::Password); // 비밀번호 숨김 처리
    noteEdit = new QLineEdit();

    form->addRow("이름:", nameEdit);
    form->addRow("전화번호:", phoneEdit);
    form->addRow("생년월일:", birthEdit);
    form->addRow("ID:", idLayout);
    form->addRow("Password:", pwEdit);
    form->addRow("비고:", noteEdit);

    /**
     * @brief 함수 기능: ID 중복 확인 버튼 클릭 처리 (Lambda)
     * @param 없음 (슬롯)
     * @return 없음
     */
    connect(btnCheck, &QPushButton::clicked, [this]()
            {
                // [핵심 원리]: 사용자가 입력한 ID 텍스트를 QStringList인 m_existingIds와 비교(contains)하여 존재 여부를 판단함.
                if (m_existingIds.contains(idEdit->text()))
                {
                    QMessageBox::warning(this, "경고", "이미 사용 중인 ID입니다.");
                    m_isIdChecked = false;
                }
                else
                {
                    QMessageBox::information(this, "알림", "사용 가능한 ID입니다.");
                    m_isIdChecked = true; // [핵심 원리]: 결과에 따라 m_isIdChecked 플래그를 업데이트함.
                }
            });

    /**
     * @brief 함수 기능: 확인/취소 버튼 처리 및 최종 검증 (Lambda)
     * @param 없음 (슬롯)
     * @return 없음
     */
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, [this]()
            {
                // [핵심 원리]: 사용자가 OK 버튼을 눌렀을 때, m_isIdChecked가 true(중복 확인 완료)인지 검사함.
                if (!m_isIdChecked)
                {
                    QMessageBox::warning(this, "알림", "중복 확인을 먼저 수행하세요.");
                }
                else
                {
                    // [핵심 원리]: 검증 통과 시 accept()를 호출하여 대화 상자를 '성공' 상태로 닫음.
                    accept();
                }
            });
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    form->addWidget(buttons);
}

/**
 * @brief 함수 기능: 기존 학생 정보를 입력란에 로드
 * @param name, phone, birth, id, pw, note: 각각의 학생 정보 필드 값
 * @return 없음
 */
void StudentDialog::setStudentData(const QString& name, const QString& phone, const QString& birth, const QString& id, const QString& pw, const QString& note)
{
    // [핵심 원리]: 수정 모드에서는 기존 학생 객체의 정보를 UI 필드에 채워 넣음.
    nameEdit->setText(name);
    phoneEdit->setText(phone);
    birthEdit->setText(birth);
    idEdit->setText(id);
    pwEdit->setText(pw);
    noteEdit->setText(note);

    // [핵심 원리]: ID는 고유 식별자이므로 수정을 제한(setEnabled(false))하며, 기존 회원이므로 체크 완료 처리함.
    idEdit->setEnabled(false);
    m_isIdChecked = true;
    setWindowTitle("학생 정보 수정");
}