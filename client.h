#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

    void connectToServer(QString host = "127.0.0.1", int port = 12345);
    void sendLogin(QString id, QString pw);

signals:
    void loginResult(bool success, QString msgs);
    void connected();
    void disconnected();

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* socket;
};

#endif // CLIENT_H
