#include "admin_window.h"

#include "student_dialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QHeaderView>
#include <QMouseEvent>
#include <QSpinBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>

Adminwindow::Adminwindow(QJsonArray usersInfo, Client *client, QWidget *parent) : QWidget(parent)
{
    this->client = client;
    setupUI();
    loadData(usersInfo);
    setWindowTitle("관리자 모드"); // 윈도우 타이틀
    resize(1100, 700); // 윈도우 사이즈
}

// UI 설정
void Adminwindow::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 사이드바
    QWidget *sidebar = new QWidget();
    sidebar->setStyleSheet("background-color: #2c3e50;"); // 색상 설정
    sidebar->setFixedWidth(200);
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    QStringList menus = {"학생 정보 관리", "학생 출결 정보 관리", "프로그램 종료"};
    stackedWidget = new QStackedWidget();

    // 메뉴별 설정
    for (int i = 0; i < menus.size(); ++i)
    {
        QPushButton *btn = new QPushButton(menus[i]);
        btn->setStyleSheet("color: white; background: transparent; text-align: left; padding: 15px; border: none;");
        sidebarLayout->addWidget(btn);

        // 페이지 생성 및 추가
        if (i == 0)
        {
            stackedWidget->addWidget(createStudentPage());
        }
        else if (i == 1)
        {
            stackedWidget->addWidget(createAttendanceStatusPage());
        }
        else
        {
            stackedWidget->addWidget(new QLabel(menus[i] + " 페이지", this));
        }

        // 통합된 버튼 클릭 연결
        connect(btn, &QPushButton::clicked, [this, i]()
                {
                    if (i == 2) // 프로그램 종료 버튼 (인덱스 2)
                    {
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(this, "프로그램 종료 확인", "프로그램을 종료 하시겠습니까?",
                                                      QMessageBox::Yes | QMessageBox::No);

                        if (reply == QMessageBox::Yes)
                        {
                            emit logoutRequested(); // 신호 발생
                            this->close();          // 현재 창 닫기
                        }
                    }
                    else
                    {
                        stackedWidget->setCurrentIndex(i);
                    }
                });
    }
    sidebarLayout->addStretch();
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
}

/**
 * @brief 학생정보 관리페이지
 * @return
 */
QWidget* Adminwindow::createStudentPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);
    QHBoxLayout *actionToolbar = new QHBoxLayout();

    searchOpt = new QComboBox();
    searchOpt->addItems({"이름", "ID", "전화번호"});
    searchEdit = new QLineEdit();
    QPushButton *btnSearch = new QPushButton("조회");

    // 위젯 추가
    actionToolbar->addWidget(searchOpt);
    actionToolbar->addWidget(searchEdit);
    actionToolbar->addWidget(btnSearch);
    actionToolbar->addStretch();

    QPushButton *btnAdd = new QPushButton("추가");
    QPushButton *btnEdit = new QPushButton("수정");
    QPushButton *btnDelete = new QPushButton("삭제");
    QPushButton *btnSave = new QPushButton("저장");

    // 위젯 추가
    actionToolbar->addWidget(btnAdd);
    actionToolbar->addWidget(btnEdit);
    actionToolbar->addWidget(btnDelete);
    actionToolbar->addWidget(btnSave);

    layout->addLayout(actionToolbar);

    // 테이블 설정
    studentTable = new QTableWidget(0, 6);
    studentTable->setHorizontalHeaderLabels({"이름", "전화번호", "생년월일", "ID", "Password", "비고"});
    studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 이벤트 필터 설치
    studentTable->viewport()->installEventFilter(this);

    // 선택 행 하이라이트 및 스타일 설정
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
    connect(btnSave, &QPushButton::clicked, this, &Adminwindow::on_btnSave_clicked);
    connect(btnDelete, &QPushButton::clicked, this, &Adminwindow::on_btnDelete_clicked);

    return page;
}

QWidget* Adminwindow::createAttendanceStatusPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 조회 툴바 추가
    QHBoxLayout *searchLayout = new QHBoxLayout();

    // 검색 옵션 콤보박스
    QComboBox *attSearchOpt = new QComboBox();
    attSearchOpt->addItems({"이름", "ID", "전화번호"}); // 검색 옵션 설정

    QLineEdit *attSearchEdit = new QLineEdit();
    attSearchEdit->setPlaceholderText("검색어를 입력하세요...");
    QPushButton *btnSearch = new QPushButton("조회");
    QPushButton *btnAttEdit = new QPushButton("수정");

    searchLayout->addWidget(new QLabel("검색:"));
    searchLayout->addWidget(attSearchOpt); // 콤보박스 추가
    searchLayout->addWidget(attSearchEdit);
    searchLayout->addWidget(btnSearch);
    searchLayout->addWidget(btnAttEdit);
    searchLayout->addStretch();
    layout->addLayout(searchLayout);

    // 테이블 구성
    attendanceTable = new QTableWidget(0, 11);
    // 각 컬럼 헤더 설정: 학생명, 전화번호, ID, 진도(진행일수/전체일수), 출석, 지각, 조퇴, 외출, 결석, 출석률, 진행률
    attendanceTable->setHorizontalHeaderLabels({"학생명", "전화번호", "ID", "진도/전체", "출석", "지각", "조퇴", "외출", "결석", "출석률", "결석률"});
    attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 기존 스타일 유지
    attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    attendanceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    attendanceTable->setSelectionMode(QAbstractItemView::SingleSelection);

    layout->addWidget(attendanceTable);

    // 조회 기능 연결 (검색 함수 사용)
    connect(btnSearch, &QPushButton::clicked, [this, attSearchOpt, attSearchEdit]()
            {
                filterTable(attendanceTable, attSearchOpt, attSearchEdit);
            });
    connect(btnAttEdit, &QPushButton::clicked, this, &Adminwindow::on_btnAttEdit_clicked);

    return page;
}

/**
 * @brief 마우스 이벤트 처리 로직
 * @param obj
 * @param event
 * @return
 */
bool Adminwindow::eventFilter(QObject *obj, QEvent *event)
{
    // 테이블의 뷰포트에서 마우스 클릭 이벤트가 발생했는지 확인
    if (obj == studentTable->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // 클릭한 위치에 아이템이 있는지 확인
        if (!studentTable->indexAt(mouseEvent->pos()).isValid())
        {
            // 아이템이 없는 빈 공간이면 선택 해제
            studentTable->clearSelection();
            studentTable->setCurrentCell(-1, -1);
        }
    }
    // 부모 클래스의 이벤트 처리 유지
    return QWidget::eventFilter(obj, event);
}

// 슬롯 함수들
/**
 * @brief 조회 기능 (선택된 옵션과 검색어에 따라 테이블 필터링)
 */
void Adminwindow::on_btnSearch_clicked()
{
    filterTable(studentTable, searchOpt, searchEdit);
}

/**
 * @brief  추가 기능 (행 추가)
 */
void Adminwindow::on_btnAdd_clicked()
{
    QStringList existingIds = studentDatabase.keys();

    // 수집된 목록을 다이얼로그로 전달
    StudentDialog dialog(existingIds, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        Student s;
        s.name = dialog.getName();
        s.phone = dialog.getPhone();
        s.birth = dialog.getBirth();
        s.id = dialog.getID();
        s.pw = dialog.getPW();
        s.note = dialog.getNote();

        studentDatabase[s.id] = s;

        refreshStudentTable();
        refreshAttendanceTable();

        // 새로 추가된 유저를 서버로 전송 (editUser가 upsert 역할을 하도록 서버 수정됨)
        if (client) {
            QJsonObject user;
            user["name"] = s.name;
            user["birthday"] = s.birth;
            user["id"] = s.id;
            user["password"] = s.pw;
            user["phoneNum"] = s.phone;
            client->sendSignUp(user);
        }
    }
}

/**
 * @brief 데이터 수정
 */
void Adminwindow::on_btnEdit_clicked()
{
    int row = studentTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "수정할 학생을 먼저 선택하세요.");
        return;
    }

    QString id = studentTable->item(row, 3) ? studentTable->item(row, 3)->text() : "";
    if (!studentDatabase.contains(id))
    {
        return;
    }

    Student s = studentDatabase[id];

    StudentDialog dialog(QStringList(), this);
    dialog.setStudentData(s.name, s.phone, s.birth, s.id, s.pw, s.note);

    if (dialog.exec() == QDialog::Accepted)
    {
        studentDatabase[id].name = dialog.getName();
        studentDatabase[id].phone = dialog.getPhone();
        studentDatabase[id].birth = dialog.getBirth();
        // ID는 변경 안함
        studentDatabase[id].pw = dialog.getPW();
        studentDatabase[id].note = dialog.getNote();

        refreshStudentTable();
        refreshAttendanceTable();
        
        // 서버로 수정 내역 전송
        if (client) {
            client->sendEditUser(studentToJson(studentDatabase[id]));
        }
    }
}

/**
 * @brief 출결 정보 수정
 */
void Adminwindow::on_btnAttEdit_clicked()
{
    int row = attendanceTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "출결을 수정할 학생을 먼저 선택하세요.");
        return;
    }

    QString id = attendanceTable->item(row, 2) ? attendanceTable->item(row, 2)->text() : "";
    if (!studentDatabase.contains(id))
    {
        return;
    }

    Student s = studentDatabase[id];

    QDialog dialog(this);
    dialog.setWindowTitle("출결 정보 수정");
    QFormLayout form(&dialog);

    QSpinBox *spinPresent = new QSpinBox(&dialog);
    QSpinBox *spinLate = new QSpinBox(&dialog);
    QSpinBox *spinEarly = new QSpinBox(&dialog);
    QSpinBox *spinOut = new QSpinBox(&dialog);
    QSpinBox *spinAbs = new QSpinBox(&dialog);

    // Set ranges
    spinPresent->setRange(0, 100);
    spinLate->setRange(0, 100);
    spinEarly->setRange(0, 100);
    spinOut->setRange(0, 100);
    spinAbs->setRange(0, 100);

    // Set current values
    spinPresent->setValue(s.attendance.present);
    spinLate->setValue(s.attendance.late);
    spinEarly->setValue(s.attendance.early);
    spinOut->setValue(s.attendance.out);
    spinAbs->setValue(s.attendance.abs);

    form.addRow("출석:", spinPresent);
    form.addRow("지각:", spinLate);
    form.addRow("조퇴:", spinEarly);
    form.addRow("외출:", spinOut);
    form.addRow("결석:", spinAbs);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        studentDatabase[id].attendance.present = spinPresent->value();
        studentDatabase[id].attendance.late = spinLate->value();
        studentDatabase[id].attendance.early = spinEarly->value();
        studentDatabase[id].attendance.out = spinOut->value();
        studentDatabase[id].attendance.abs = spinAbs->value();

        refreshAttendanceTable();
        refreshStudentTable();

        if (client) {
            client->sendEditUser(studentToJson(studentDatabase[id]));
        }
    }
}

/**
 * @brief 학생 정보를 Json 형식으로 변환
 * @param s 학생 정보
 * @return
 */
QJsonObject Adminwindow::studentToJson(const Student& s)
{
    QJsonObject obj;
    obj["id"] = s.id;
    obj["note"] = s.note;
    
    QJsonObject info;
    info["name"] = s.name;
    info["password"] = s.pw;
    info["phoneNum"] = s.phone;
    info["birthday"] = s.birth;
    
    // Calculate age (simple logic)
    QDate birthDate = QDate::fromString(s.birth, Qt::ISODate);
    if(birthDate.isValid()) {
        info["age"] = QDate::currentDate().year() - birthDate.year() + 1;
    } else {
        info["age"] = 0;
    }
    
    obj["info"] = info;
    
    QJsonObject attendance;
    attendance["present"] = s.attendance.present;
    attendance["late"] = s.attendance.late;
    attendance["earlyLeave"] = s.attendance.early;
    attendance["beOut"] = s.attendance.out;
    attendance["absent"] = s.attendance.abs;
    
    obj["attendance"] = attendance;
    
    return obj;
}

/**
 * @brief 데이터 저장
 */
void Adminwindow::on_btnSave_clicked()
{
    saveData();
    QMessageBox::information(this, "알림", "모든 데이터가 저장되었습니다.");
}

/**
 * @brief 삭제 기능 (선택된 행 삭제)
 */
void Adminwindow::on_btnDelete_clicked()
{
    int row = studentTable->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "알림", "삭제할 학생을 선택하세요.");
        return;
    }
    if (QMessageBox::question(this, "삭제 확인", "정말 삭제하시겠습니까?") == QMessageBox::Yes)
    {
        QString id = studentTable->item(row, 3) ? studentTable->item(row, 3)->text() : "";
        studentDatabase.remove(id);

        refreshStudentTable();
        refreshAttendanceTable();

        if (client) {
            client->sendWithdraw(id);
        }
    }
}

/**
 * @brief 정보 저장
 */
void Adminwindow::saveData()
{
    qDebug() << "save Data in json...";
    QJsonArray studentArray;

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        QJsonObject obj;
        obj["id"] = s.id;
        obj["pw"] = s.pw;
        obj["name"] = s.name;
        obj["phone"] = s.phone;
        obj["birth"] = s.birth;
        obj["note"] = s.note;

        QJsonObject attObj;
        attObj["totalDays"] = s.attendance.totalDays;
        attObj["completedDays"] = s.attendance.completedDays;
        attObj["present"] = s.attendance.present;
        attObj["late"] = s.attendance.late;
        attObj["early"] = s.attendance.early;
        attObj["out"] = s.attendance.out;
        attObj["abs"] = s.attendance.abs;

        obj["attendance_summary"] = attObj;
        studentArray.append(obj);
    }

    QJsonObject root;
    root["students"] = studentArray;

    QJsonDocument doc(root);
    QFile file("students.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}

/**
 * @brief 저장된 JSON 파일에서 데이터를 읽어와 메모리(studentDatabase)에 적재하고 테이블 갱신
 * @param array
 */
void Adminwindow::loadData(const QJsonArray &array)
{
    qDebug() << "load data from server";
    studentDatabase.clear();

    for (const QJsonValue &value : std::as_const(array))
    {
        QJsonObject obj = value.toObject();
        Student s;
        s.id = obj["id"].toString();
        
        QJsonObject info = obj["info"].toObject();
        s.pw = info["password"].toString();
        s.name = info["name"].toString();
        s.phone = info["phoneNum"].toString();
        s.birth = info["birthday"].toString();
        s.note = obj["note"].toString(); // Assuming note might be at root or empty

        QJsonObject attendance = obj["attendance"].toObject();
        s.attendance.present = attendance["present"].toInt();
        s.attendance.late = attendance["late"].toInt();
        s.attendance.early = attendance["earlyLeave"].toInt();
        s.attendance.out = attendance["beOut"].toInt();
        s.attendance.abs = attendance["absent"].toInt();
        
        // Calculate completedDays if not explicitly provided
        s.attendance.completedDays = s.attendance.present + s.attendance.late + 
                                     s.attendance.early + s.attendance.out + s.attendance.abs;
        if(s.attendance.completedDays == 0 && obj.contains("attendance_summary"))
        {
            QJsonObject attObj = obj["attendance_summary"].toObject();
            s.attendance.totalDays = attObj["totalDays"].toInt(100);
            s.attendance.completedDays = attObj["completedDays"].toInt(0);
            s.attendance.present = attObj["present"].toInt(0);
            s.attendance.early = attObj["early"].toInt(0);
            s.attendance.out = attObj["out"].toInt(0);
            s.attendance.abs = attObj["abs"].toInt(0);
        }

        studentDatabase[s.id] = s;
    }

    refreshStudentTable();
    refreshAttendanceTable();
}

/**
 * @brief 학생 정보 테이블 재조회(데이터 수정 등에 의한 변경 시)
 */
void Adminwindow::refreshStudentTable()
{
    if (!studentTable)
    {
        return;
    }
    studentTable->setRowCount(0);

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        int row = studentTable->rowCount();
        studentTable->insertRow(row);

        QTableWidgetItem *nameItem = new QTableWidgetItem(s.name);
        nameItem->setData(Qt::UserRole, s.id); // 검색용 ID 저장
        studentTable->setItem(row, 0, nameItem);
        studentTable->setItem(row, 1, new QTableWidgetItem(s.phone));
        studentTable->setItem(row, 2, new QTableWidgetItem(s.birth));
        studentTable->setItem(row, 3, new QTableWidgetItem(s.id));
        studentTable->setItem(row, 4, new QTableWidgetItem(s.pw));
        studentTable->setItem(row, 5, new QTableWidgetItem(s.note));

        for (int i = 0; i < 6; ++i)
        {
            if (studentTable->item(row, i))
            {
                studentTable->item(row, i)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

/**
 * @brief 출결 관리 정보 페이지 재조회(정보 수정 등에 의한 변경 시)
 */
void Adminwindow::refreshAttendanceTable()
{
    if (!attendanceTable)
    {
        return;
    }
    attendanceTable->setRowCount(0);

    for (auto it = studentDatabase.begin(); it != studentDatabase.end(); ++it)
    {
        const Student &s = it.value();
        int row = attendanceTable->rowCount();
        attendanceTable->insertRow(row);

        int effective_absent = s.attendance.abs + (s.attendance.late + s.attendance.early + s.attendance.out) / 3;
        double absentRate = effective_absent; // 100일 기준 결석률
        double attendanceRate = 100.0 - effective_absent; // 100일 기준 출석률

        QTableWidgetItem *nameItem = new QTableWidgetItem(s.name);
        nameItem->setData(Qt::UserRole, s.id); // 검색용 ID 저장
        attendanceTable->setItem(row, 0, nameItem);
        attendanceTable->setItem(row, 1, new QTableWidgetItem(s.phone));
        attendanceTable->setItem(row, 2, new QTableWidgetItem(s.id)); // 학생 ID
        // 진도는 출석 / 100
        attendanceTable->setItem(row, 3, new QTableWidgetItem(QString("%1 / 100").arg(s.attendance.present)));
        attendanceTable->setItem(row, 4, new QTableWidgetItem(QString::number(s.attendance.present))); // 출석 횟수
        attendanceTable->setItem(row, 5, new QTableWidgetItem(QString::number(s.attendance.late)));    // 지각 횟수
        attendanceTable->setItem(row, 6, new QTableWidgetItem(QString::number(s.attendance.early)));   // 조퇴 횟수
        attendanceTable->setItem(row, 7, new QTableWidgetItem(QString::number(s.attendance.out)));     // 외출 횟수
        attendanceTable->setItem(row, 8, new QTableWidgetItem(QString::number(s.attendance.abs)));     // 결석 횟수
        attendanceTable->setItem(row, 9, new QTableWidgetItem(QString::number(attendanceRate, 'f', 1) + "%")); // 출석률
        attendanceTable->setItem(row, 10, new QTableWidgetItem(QString::number(absentRate, 'f', 1) + "%"));  // 결석률

        for (int col = 0; col < 11; ++col)
        {
            if (attendanceTable->item(row, col))
            {
                attendanceTable->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

/**
 * @brief 공통 검색 헬퍼 함수
 * @param table
 * @param combo
 * @param edit
 */
void Adminwindow::filterTable(QTableWidget *table, QComboBox *combo, QLineEdit *edit)
{
    QString option = combo->currentText();
    QString keyword = edit->text().trimmed();

    for (int i = 0; i < table->rowCount(); ++i)
    {
        bool match = false;

        if (option == "ID")
        {
            // ID는 항상 0번 컬럼(이름)의 UserRole 데이터에 숨겨져 있음
            QTableWidgetItem *item = table->item(i, 0);
            if (item && item->data(Qt::UserRole).toString().contains(keyword, Qt::CaseInsensitive))
            {
                match = true;
            }
        }
        else if (option == "이름")
        {
            QTableWidgetItem *item = table->item(i, 0); // 두 테이블 모두 0번이 이름
            if (item && item->text().contains(keyword, Qt::CaseInsensitive))
            {
                match = true;
            }
        }
        else if (option == "전화번호")
        {
            QTableWidgetItem *item = table->item(i, 1); // 두 테이블 모두 1번이 전화번호
            if (item && item->text().contains(keyword, Qt::CaseInsensitive))
            {
                match = true;
            }
        }

        table->setRowHidden(i, !match);
    }
}