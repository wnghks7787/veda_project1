/**
 * 유저 정보를 담는 클래스
 * */

#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

#include "client.h"

class User
{
public:
    User();
    User(QJsonObject userJson);
    ~User();

    // 각각 필요한 getter() / setter()들
    QString getName() const;
    void setName(const QString &newName);
    QDate getBirthday() const;
    void setBirthday(const QDate &newBirthday);
    QString getId() const;
    void setId(const QString &newId);
    QString getPassword() const;
    void setPassword(const QString &newPassword);
    QString getPhoneNum() const;
    void setPhoneNum(const QString &newphoneNum);
    int getAge() const;
    void setAge(int newAge);

    int getPresent() const;
    int getAbsent() const;
    int getLate() const;
    int getEarlyLeave() const;
    int getBeOut() const;

    QJsonObject getUserJson();

    void withdraw(); // 사용자 회원 탈퇴

private:
    QString id; // 아이디

    // user info
    QString name; // 이름
    QDate birthday; // 생년월일
    QString password; // 비밀번호
    QString phoneNum; // 전화번호
    int age; // 나이

    // attendance ( 지각/조퇴/외출 총 3회당 결석 1회)
    int present; // 출석
    int absent; // 결석
    int late; // 지각
    int earlyLeave; // 조퇴
    int beOut; // 외출

    Client* client;
};

#endif // USER_H
