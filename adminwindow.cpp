//관리자 모드 UI
#include "adminwindow.h"
#include <QHeaderView>
#include <QMouseEvent>
Adminwindow::Adminwindow(QWidget *parent) : QWidget(parent)
{
    setupUI();
    //loadDummyData();
    loadData();
    setWindowTitle("관리자 모드");
    resize(1100, 700);
}
void Adminwindow::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    // 1. 사이드바
    QWidget *sidebar = new QWidget();
    sidebar->setStyleSheet("background-color: #2c3e50;");
    sidebar->setFixedWidth(200);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    QStringList menus = {"학생 정보 관리","일별 출결 현황","학생 출결 정보 관리","로그아웃"};
    stackedWidget = new QStackedWidget();

    for(int i=0; i<menus.size(); ++i)
    {
        QPushButton *btn = new QPushButton(menus[i]);
        btn->setStyleSheet("color: white; background: transparent; text-align: left; padding: 15px; border: none;");
        sidebarLayout->addWidget(btn);

        if(i == 0)
        {
            stackedWidget->addWidget(createStudentPage());
        }
        else if(i == 2)
        {
            stackedWidget->addWidget(createAttendanceStatusPage());
        }
        else
        {
            stackedWidget->addWidget(new QLabel(menus[i] + " 페이지", this));
        }

        connect(btn, &QPushButton::clicked, [this, i]()
                {
                    stackedWidget->setCurrentIndex(i);
                });
    }
    sidebarLayout->addStretch();

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
}
//학생 정보 관리 페이지
QWidget* Adminwindow::createStudentPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    QHBoxLayout *actionToolbar = new QHBoxLayout();

    searchOpt = new QComboBox();
    searchOpt->addItems({"이름", "전화번호", "ID"});
    searchEdit = new QLineEdit();
    QPushButton *btnSearch = new QPushButton("조회");

    actionToolbar->addWidget(searchOpt);
    actionToolbar->addWidget(searchEdit);
    actionToolbar->addWidget(btnSearch);
    actionToolbar->addStretch();

    QPushButton *btnAdd = new QPushButton("추가");
    QPushButton *btnEdit = new QPushButton("저장");
    QPushButton *btnDelete = new QPushButton("삭제");

    actionToolbar->addWidget(btnAdd);
    actionToolbar->addWidget(btnEdit);
    actionToolbar->addWidget(btnDelete);

    layout->addLayout(actionToolbar);

    // 테이블 설정
    studentTable = new QTableWidget(0, 6);
    studentTable->setHorizontalHeaderLabels({"이름", "전화번호", "생년월일", "ID", "Password", "비고"});

    // 이벤트 필터 설치
    studentTable->viewport()->installEventFilter(this);

    // [시각적 개선] 선택 행 하이라이트 및 스타일 설정
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentTable->setStyleSheet(
        "QTableWidget::item:selected {"
        "   background-color: #3498db;"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        "QTableWidget { alternate-background-color: #f2f2f2; }"
        );
    studentTable->setAlternatingRowColors(true);

    studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(studentTable);

    // 슬롯 연결
    connect(btnSearch, &QPushButton::clicked, this, &Adminwindow::on_btnSearch_clicked);
    connect(btnAdd, &QPushButton::clicked, this, &Adminwindow::on_btnAdd_clicked);
    connect(btnEdit, &QPushButton::clicked, this, &Adminwindow::on_btnEdit_clicked);
    connect(btnDelete, &QPushButton::clicked, this, &Adminwindow::on_btnDelete_clicked);

    return page;
}
/*
QWidget* Adminwindow::createAttendancePage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 1. Action Toolbar 구성
    QHBoxLayout *actionToolbar = new QHBoxLayout();

    // 날짜 선택기 추가 (사용성을 위해)
    actionToolbar->addWidget(new QLabel("날짜:"));
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    actionToolbar->addWidget(dateEdit);

    QPushButton *btnSearch = new QPushButton("조회");
    actionToolbar->addWidget(btnSearch);

    actionToolbar->addStretch();

    QPushButton *btnSave = new QPushButton("💾 일괄 저장");
    QPushButton *btnExport = new QPushButton("📤 내보내기");

    actionToolbar->addWidget(btnSave);
    actionToolbar->addWidget(btnExport);

    layout->addLayout(actionToolbar);

    // 2. 테이블 구성 (컬럼 9개로 증가)
    // 순서: 학생명, 전화번호, 입실 시간, 퇴실 시간, 출석, 결석, 지각, 조퇴, 외출
    QTableWidget *table = new QTableWidget(0, 9);
    table->setHorizontalHeaderLabels({"학생명", "전화번호", "입실 시간", "퇴실 시간", "출석", "결석", "지각", "조퇴", "외출"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    // 컬럼 비율 자동 조절
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);


    // [중요] 이 줄이 있어야 데이터가 들어갑니다!
    loadAttendanceData(table);

    return page;
}*/

QWidget* Adminwindow::createAttendanceStatusPage() {
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 1. 조회 툴바 추가
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("학생명 또는 전화번호 검색...");
    QPushButton *btnSearch = new QPushButton("🔍 조회");

    searchLayout->addWidget(new QLabel("검색:"));
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(btnSearch);
    searchLayout->addStretch();
    layout->addLayout(searchLayout);

    // 2. 테이블 구성 (컬럼을 10개로 증가)
    // 순서: 학생명, 전화번호, 진도/전체, 출석, 지각, 조퇴, 외출, 결석, 출석률, 진행률
    QTableWidget *table = new QTableWidget(0, 10);
    table->setHorizontalHeaderLabels({"학생명", "전화번호", "진도/전체", "출석", "지각", "조퇴", "외출", "결석", "출석률", "진행률"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    // 데이터 구조 정의
    struct StudentData {
        QString name, phone;
        int totalDays, completedDays, present, late, early, out, abs;
    };

    QList<StudentData> studentList = {
        {"김철수", "010-1234-5678", 100, 50, 45, 2, 0, 0, 3},
        {"이영희", "010-9876-5432", 100, 50, 40, 0, 4, 0, 6},
        {"박민수", "010-5555-4444", 100, 50, 30, 4, 4, 4, 8}
    };

    table->setRowCount(studentList.size());

    // 3. 데이터 입력
    for (int i = 0; i < studentList.size(); ++i) {
        StudentData s = studentList[i];

        double attendanceRate = (static_cast<double>(s.present) / s.completedDays) * 100.0;
        double progressRate = (static_cast<double>(s.completedDays) / s.totalDays) * 100.0;

        table->setItem(i, 0, new QTableWidgetItem(s.name));
        table->setItem(i, 1, new QTableWidgetItem(s.phone)); // 전화번호 추가
        table->setItem(i, 2, new QTableWidgetItem(QString("%1 / %2").arg(s.completedDays).arg(s.totalDays)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(s.present)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(s.late)));
        table->setItem(i, 5, new QTableWidgetItem(QString::number(s.early)));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(s.out)));
        table->setItem(i, 7, new QTableWidgetItem(QString::number(s.abs)));
        table->setItem(i, 8, new QTableWidgetItem(QString::number(attendanceRate, 'f', 1) + "%"));
        table->setItem(i, 9, new QTableWidgetItem(QString::number(progressRate, 'f', 1) + "%"));

        for(int col = 0; col < 10; ++col) table->item(i, col)->setTextAlignment(Qt::AlignCenter);
    }

    // 4. 조회 기능 연결 (람다 함수 사용)
    connect(btnSearch, &QPushButton::clicked, [table, searchEdit]() {
        QString keyword = searchEdit->text().trimmed();
        for (int i = 0; i < table->rowCount(); ++i) {
            bool match = table->item(i, 0)->text().contains(keyword, Qt::CaseInsensitive) ||
                         table->item(i, 1)->text().contains(keyword);
            table->setRowHidden(i, !match); // 조건에 맞지 않으면 행 숨기기
        }
    });

    return page;
}
/*
void Adminwindow::loadAttendanceData(QTableWidget *table) {
    table->setRowCount(3); // 3명의 데이터

    // 데이터 정의: {이름, 전화번호, 입실, 퇴실, 출석, 결석, 지각, 조퇴, 외출}
    // "O" 표시를 사용하여 출석 상태를 직관적으로 표현했습니다.
    QStringList student1 = {"김철수", "010-1234-5678", "09:00", "18:00", "O", "", "", "", ""};
    QStringList student2 = {"이영희", "010-9876-5432", "09:15", "18:00", "", "", "O", "", ""};
    QStringList student3 = {"박민수", "010-5555-4444", "08:50", "15:00", "", "", "", "O", ""};

    QList<QStringList> data = {student1, student2, student3};

    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < 9; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(data[i][j]);

            // 텍스트 가운데 정렬
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(i, j, item);
        }
    }
}*/
bool Adminwindow::eventFilter(QObject *obj, QEvent *event)
{
    // 테이블의 뷰포트에서 마우스 클릭 이벤트가 발생했는지 확인
    if (obj == studentTable->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // 클릭한 위치에 아이템이 있는지 확인
        if (!studentTable->indexAt(mouseEvent->pos()).isValid()) {
            // 아이템이 없는 빈 공간이면 선택 해제
            studentTable->clearSelection();
            studentTable->setCurrentCell(-1, -1);
        }
    }
    // 부모 클래스의 이벤트 처리 유지
    return QWidget::eventFilter(obj, event);
}
// --- 아래는 모든 슬롯 함수 구현입니다 (adminwindow 클래스 소속) ---
// 1. 조회 기능 (선택된 옵션과 검색어에 따라 테이블 필터링)
void Adminwindow::on_btnSearch_clicked()
{
    QString keyword = searchEdit->text().trimmed();
    int targetColumn = 0; // "이름" (기본값)

    if (searchOpt->currentText() == "전화번호") targetColumn = 1;
    else if (searchOpt->currentText() == "ID") targetColumn = 4;

    for (int i = 0; i < studentTable->rowCount(); ++i) {
        QTableWidgetItem *item = studentTable->item(i, targetColumn);
        bool match = (item && item->text().contains(keyword, Qt::CaseInsensitive));
        studentTable->setRowHidden(i, !match);
    }
}
// 2. 추가 기능 (행 추가)
void Adminwindow::on_btnAdd_clicked()
{
    // 1. 현재 테이블에서 기존 ID 목록 수집
    QStringList existingIds;
    for (int i = 0; i < studentTable->rowCount(); ++i)
    {
        if (studentTable->item(i, 4))
        {
            existingIds.append(studentTable->item(i, 4)->text());
        }
    }

    // 2. 수집된 목록을 다이얼로그로 전달
    AddStudentDialog dialog(existingIds, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        int newRow = studentTable->rowCount();
        studentTable->insertRow(newRow);

        studentTable->setItem(newRow, 0, new QTableWidgetItem(dialog.getName()));
        studentTable->setItem(newRow, 1, new QTableWidgetItem(dialog.getPhone()));
        //studentTable->setItem(newRow, 2, new QTableWidgetItem(dialog.getAge()));
        studentTable->setItem(newRow, 2, new QTableWidgetItem(dialog.getBirth()));
        studentTable->setItem(newRow, 3, new QTableWidgetItem(dialog.getID()));
        studentTable->setItem(newRow, 4, new QTableWidgetItem(dialog.getPW()));
        studentTable->setItem(newRow, 5, new QTableWidgetItem(dialog.getNote()));

        for(int i = 0; i < 6; ++i)
        {
            if(studentTable->item(newRow, i))
                studentTable->item(newRow, i)->setTextAlignment(Qt::AlignCenter);
        }
    }
}
//데이터
void Adminwindow::on_btnEdit_clicked()
{
    int row = studentTable->currentRow();
    if (row < 0)
    {
        saveData();
        QMessageBox::warning(this, "알림", "수정사항이 저장되었습니다");
        return;
    }
}
// 4. 삭제 기능 (선택된 행 삭제)
void Adminwindow::on_btnDelete_clicked() {
    int row = studentTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "삭제할 학생을 선택하세요.");
        return;
    }
    if (QMessageBox::question(this, "삭제 확인", "정말 삭제하시겠습니까?") == QMessageBox::Yes)
    {
        studentTable->removeRow(row);
    }
}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ더미 데이터 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
/*void Adminwindow::loadDummyData() {
    // 1. 행 2개 만들기
    studentTable->setRowCount(2);

    // 2. 1행 데이터 직접 삽입
    studentTable->setItem(0, 0, new QTableWidgetItem("김철수"));
    studentTable->setItem(0, 1, new QTableWidgetItem("010-1234-5678"));
    studentTable->setItem(0, 2, new QTableWidgetItem("20"));
    studentTable->setItem(0, 3, new QTableWidgetItem("2006-05-12"));
    studentTable->setItem(0, 4, new QTableWidgetItem("chulsoo"));
    studentTable->setItem(0, 5, new QTableWidgetItem("1234"));
    studentTable->setItem(0, 6, new QTableWidgetItem("양호"));

    // 3. 2행 데이터 직접 삽입
    studentTable->setItem(1, 0, new QTableWidgetItem("이영희"));
    studentTable->setItem(1, 1, new QTableWidgetItem("010-9876-5432"));
    studentTable->setItem(1, 2, new QTableWidgetItem("21"));
    studentTable->setItem(1, 3, new QTableWidgetItem("2005-03-21"));
    studentTable->setItem(1, 4, new QTableWidgetItem("younghee"));
    studentTable->setItem(1, 5, new QTableWidgetItem("5678"));
    studentTable->setItem(1, 6, new QTableWidgetItem("특이사항 없음"));

    // 4. 정렬 (필요시)
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 7; j++) {
            if(studentTable->item(i, j))
                studentTable->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}*/
/*void Adminwindow::loadDummyData(){
    studentTable->setRowCount(2);

    // 학생 1: 김철수
    studentTable->setItem(0, 0, new QTableWidgetItem("김철수"));
    studentTable->setItem(0, 1, new QTableWidgetItem("010-1234-5678"));
    studentTable->setItem(0, 2, new QTableWidgetItem("20"));
    studentTable->setItem(0, 3, new QTableWidgetItem("2006-05-12"));
    studentTable->setItem(0, 4, new QTableWidgetItem("chulsoo"));
    studentTable->setItem(0, 5, new QTableWidgetItem("1234")); // 비밀번호는 보통 가림
    studentTable->setItem(0, 6, new QTableWidgetItem("양호"));

    // 학생 2: 이영희
    studentTable->setItem(1, 0, new QTableWidgetItem("이영희"));
    studentTable->setItem(1, 1, new QTableWidgetItem("010-9876-5432"));
    studentTable->setItem(1, 2, new QTableWidgetItem("21"));
    studentTable->setItem(1, 3, new QTableWidgetItem("2005-03-21"));
    studentTable->setItem(1, 4, new QTableWidgetItem("younghee"));
    studentTable->setItem(1, 5, new QTableWidgetItem("5678"));
    studentTable->setItem(1, 6, new QTableWidgetItem("특이사항 없음"));
}*/