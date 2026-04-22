#include "admin_window.h"
#include "ui_widget.h"
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QHeaderView> // 컬럼 꽉 채우기 기능(Stretch)을 위해 필수

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("고객 관리 프로그램 (필터링 및 전체보기 적용)");
    this->resize(700, 450); // 버튼이 늘어났으므로 가로 길이를 조금 늘림

    // 테이블 컬럼을 화면 너비에 맞게 꽉 채움
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Widget::~Widget()
{
    delete ui;
}

// UI에서 '추가' 버튼을 더블클릭해서 자동 생성된 슬롯 함수
void Widget::on_pushButton_2_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("고객 정보 추가");

    QFormLayout form(&dialog);
    nameEdit = new QLineEdit(&dialog);
    phoneEdit = new QLineEdit(&dialog);
    ageEdit = new QLineEdit(&dialog);
    gradeEdit = new QLineEdit(&dialog);

    form.addRow("이름:", nameEdit);
    form.addRow("전화번호:", phoneEdit);
    form.addRow("나이:", ageEdit);
    form.addRow("등급:", gradeEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    //고객 정보 추가 창 띄우기 및 입력 예외처리
    if (dialog.exec() == QDialog::Accepted)
    {   // 1. 입력된 텍스트 가져오기 및 양옆 공백 제거(trimmed)
        QString name = nameEdit->text().trimmed();
        QString phone = phoneEdit->text().trimmed();
        QString ageStr = ageEdit->text().trimmed();
        QString grade = gradeEdit->text().trimmed();

        // 분리해둔 예외 처리 함수를 호출하여 검사!
        // 만약 validateInput이 false를 반환했다면 여기서 함수를 강제 종료합니다.
        if (!validateInput(name, phone, ageStr, grade))
        {
            return;
        }

        //모든 예외 처리를 무사히 통과했을 경우에만 데이터를 구조체에 넣고 테이블에 추가
        CustomerData newData;
        newData.name = name;
        newData.phone = phone;
        newData.age = ageStr;
        newData.grade = grade;

        // 데이터가 저장되었으니 테이블에 추가하는 함수 호출
        addRowToTable(newData);
    }
}

// 주석을 해제하고 m_pTableWidget을 ui->tableWidget으로 수정했습니다.
void Widget::addRowToTable(const CustomerData& data)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(data.name));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(data.phone));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(data.age));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(data.grade));
}

/*

*/
bool Widget::validateInput(const QString& name, const QString& phone, const QString& ageStr, const QString& grade)
{
    // [예외 처리 1] 빈칸 검사
    if (name.isEmpty() || phone.isEmpty() || ageStr.isEmpty() || grade.isEmpty())
    {
        QMessageBox::warning(this, "입력 오류", "모든 항목을 빈칸 없이 입력해주세요.");
        return false; // 검사 실패
    }

    // [예외 처리 2] 나이 칸 숫자 검사
    bool isNum;
    int age = ageStr.toInt(&isNum);
    if (!isNum || age <= 0)
    {
        QMessageBox::warning(this, "입력 오류", "나이는 0보다 큰 올바른 숫자로 입력해주세요.");
        return false; // 검사 실패
    }

    // [예외 처리 3] 이름 형식 검사 (주석 처리 유지)
    /* QRegularExpression nameRegex("^[가-힣a-zA-Z]+$");
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::warning(this, "입력 오류", "이름은 한글이나 영문만 입력 가능합니다.");
        return false; // 검사 실패
    }
    */

    return true; // 모든 예외 처리 무사히 통과!
}