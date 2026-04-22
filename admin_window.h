/**
 * 관리자로 로그인했을 때 볼 수 있는 화면
 * admin_window.ui를 통해 관리자 페이지 생성
 * 로그인 시 받은 정보를 통해 전체 유저의 출결 현황과 정보를 조회/수정할 수 있음
 * 새로운 사용자를 추가 / 기존 유저 삭제 가능
 * 로그아웃은 가능하나 회원탈퇴는 불가능
 * */

#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H
#include "client.h"
#include <QWidget>
#include <QStackedWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>

/**
 * @brief 출결 요약 정보를 담는 구조체
 */
struct AttendanceSummary
{
    int totalDays = 100;    // 전체 수업 일수
    int completedDays = 0; // 현재까지 진행된 수업 일수
    int present = 0;       // 출석 횟수
    int late = 0;          // 지각 횟수
    int early = 0;         // 조퇴 횟수
    int out = 0;           // 외출 횟수
    int abs = 0;           // 결석 횟수
};

/**
 * @brief 학생 정보를 담는 구조체
 */
struct Student
{
    QString id;         // 학생 ID
    QString pw;         // 비밀번호
    QString name;       // 이름
    QString phone;      // 전화번호
    QString birth;      // 생년월일
    QString note;       // 비고(메모)

    AttendanceSummary attendance; // 출결 정보
};

/**
 * @brief 관리자 메인 윈도우 클래스
 */
class Adminwindow : public QWidget
{
    Q_OBJECT

public:
    // 생성자: UI 초기화 및 데이터 로드 수행
    Adminwindow(QJsonArray usersInfo, Client *client, QWidget *parent = nullptr);

private slots:
    void on_btnAdd_clicked(); // 학생 추가 버튼 슬롯
    void on_btnEdit_clicked(); // 정보 수정 버튼 슬롯
    void on_btnSave_clicked(); // 정보 저장 버튼 슬롯
    void on_btnDelete_clicked(); // 학생 삭제 버튼 슬롯
    void on_btnSearch_clicked(); // 검색 버튼 슬롯

    void on_btnAttEdit_clicked(); // 출결 정보 수정 보튼 슬롯

private:
    void setupUI(); // 전체적인 UI 설정 함수
    QWidget* createStudentPage(); // 학생 정보 관리 페이지를 생성하는 함수
    QWidget* createAttendanceStatusPage(); // 출결 상태 확인 페이지를 생성하는 함수

    void saveData(); // 현재의 studentDatabase 메모리 데이터를 JSON 파일로 저장하는 함수
    void loadData(const QJsonArray &array); // 서버로부터 받은 데이터를 studentDatabase에 로드하는 함수
    void refreshStudentTable(); // studentDatabase의 정보를 바탕으로 학생 관리 테이블을 갱신하는 함수
    void refreshAttendanceTable(); // studentDatabase의 정보를 바탕으로 출결 현황 테이블을 갱신하는 함수
    QJsonObject studentToJson(const Student& s); // Student 구조체를 QJsonObject 포맷(서버 통신용)으로 변환하는 함수

    void filterTable(QTableWidget *table, QComboBox *combo, QLineEdit *edit); // 테이블 내의 데이터를 검색 조건(콤보박스, 입력창)에 따라 필터링하는 함수

    // 학생 ID를 키로 하는 학생 데이터 저장 맵
    QMap<QString, Student> studentDatabase;

    QStackedWidget *stackedWidget;   // 여러 페이지를 전환하기 위한 스택 위젯
    QTableWidget *studentTable;      // 학생 정보 표시 테이블
    QTableWidget *attendanceTable;   // 출결 정보 표시 테이블
    QLineEdit *searchEdit;           // 검색어 입력창
    QComboBox *searchOpt;            // 검색 옵션 선택창
    
    Client *client;                  // 서버 통신용 클라이언트 객체

signals:
    // 로그아웃이 요청되었을 때(예: 로그아웃 버튼 클릭) 발생하는 시그널
    void logoutRequested();

protected:
    // 윈도우 내의 이벤트를 감시하고 처리하기 위한 이벤트 필터
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // ADMIN_WINDOW_H