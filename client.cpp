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

/**
 * @brief 서버와 연결하는 로직. host port는 서버에 맞춰 변경 필요
 * @param host 127.0.0.1
 * @param port 12345
 */
void Client::connectToServer(QString host, int port)
{
    socket->connectToHost(host, port);
}

/**
 * @brief 로그인을 보내는 로직
 * @param id
 * @param pw
 */
void Client::sendLogin(QString id, QString pw)
{
    QJsonObject obj;

    obj["type"] = "login";
    obj["id"] = id;
    obj["password"] = pw;

    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}

/**
 * @brief 회원탈퇴 보내는 부분
 * @param id
 */
void Client::sendWithdraw(QString id)
{
    QJsonObject obj;

    obj["type"] = "withdraw";
    obj["id"] = id;

    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}

/**
 * @brief 아이디 중복 확인 보내는 부분
 * @param id
 */
void Client::sendVerifyId(QString id)
{
    QJsonObject obj;

    obj["type"] = "verifyId";
    obj["id"] = id;

    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}

/**
 * @brief 회원가입 하는 부분. user는 입력된 user정보를 보내줌
 * @param user
 */
void Client::sendSignUp(QJsonObject user)
{
    QJsonObject obj;

    obj["type"] = "signUp";
    obj["user"] = user;

    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}

/**
 * @brief 서버 연결
 */
void Client::onConnected()
{
    qDebug() << "서버 연결됨";
    emit connected();
}

/**
 * @brief 서버 연결 유실
 */
void Client::onDisconnected()
{
    qDebug() << "서버 연결 끊김";
    emit disconnected();
}

/**
 * @brief 값을 받는 부분. 상황에 따라 처리 로직이 다름. \
 * 예를 들어, type이 login이면 로그인을, verifyId면 아이디 중복체크를 하는 식
 */
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
    else if(type == "verifyId")
    {
        bool success = obj["success"].toBool();

        emit verifiedResult(success);
    }
    else if(type == "signUp")
    {
        bool success = obj["success"].toBool();

        emit signUpResult(success);
    }
}