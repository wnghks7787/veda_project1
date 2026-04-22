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

    void connectToServer(QString host = "127.0.0.1", int port = 12345);
    void sendLogin(QString id, QString pw);
    void sendWithdraw(QString id);
    void sendVerifyId(QString id);
    void sendSignUp(QJsonObject user);

signals:
    void loginResult(bool success, QJsonObject user);
    void verifiedResult(bool success);
    void signUpResult(bool success);
    void connected();
    void disconnected();

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* socket; // 클라이언트 소켓
};

#endif // CLIENT_H
