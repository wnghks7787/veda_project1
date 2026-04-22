/**
 * 서버와 통신하는 클라이언트 클래스
 * UI는 따로 존재하지 않음
 * host 부분과 port 부분을 변경하여 통신 가능(default: "127.0.0.1", 12345)
 * 요청받은 값을 서버에 전송
 * */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QtNetwork/QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

    void connectToServer(QString host = "127.0.0.1", int port = 12345); // 호스트 포트 번호를 변경하여 통신할 수 있음. 서버 설정에 맞출 것
    void sendLogin(QString id, QString pw); // 로그인 요청
    void sendWithdraw(QString id); // 회원탈퇴 요청
    void sendVerifyId(QString id); // 아이디 중복확인 요청
    void sendSignUp(QJsonObject user); // 회원가입 요청
    void sendEditUser(QJsonObject user); // 사용자 정보 변경 요청

signals:
    void loginResult(bool success, QJsonObject user); // 로그인 결과 반환(유저)
    void loginResultAdmin(bool success, QJsonObject user, QJsonArray users); // 로그인 결과 반환(관리자)
    void verifiedResult(bool success); // 아이디 중복 확인 결과 반환
    void signUpResult(bool success); // 회원가입 결과 반환
    void editUserResult(bool success); // 사용자 정보 변경 결과 반환
    void connected(); // 서버 연결
    void disconnected(); // 서버 연결 해제

private slots:
    void onConnected(); // 서버에 연결되었을 때
    void onReadyRead(); // 서버로부터 데이터를 전송받았을 때
    void onDisconnected(); // 서버에서 연결 해제 되었을 때

private:
    QTcpSocket* socket; // 클라이언트 소켓
};

#endif // CLIENT_H
