#include "client.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Client::Client(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void Client::connectToServer(QString host, int port)
{
    socket->connectToHost(host, port);
}

void Client::sendLogin(QString id, QString pw)
{
    QJsonObject obj;

    obj["type"] = "login";
    obj["id"] = id;
    obj["password"] = pw;

    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}

void Client::onConnected()
{
    qDebug() << "서버 연결됨";
    emit connected();
}

void Client::onDisconnected()
{
    qDebug() << "서버 연결 끊김";
    emit disconnected();
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString type = obj["type"].toString();

    if(type == "login")
    {
        bool success = obj["success"].toBool();
        QJsonObject user = obj["user"].toObject();

        emit loginResult(success, user);
    }
}