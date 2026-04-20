#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

class User
{
public:
    User();
    ~User();

    QString getName() const;
    void setName(const QString &newName);
    QDate getBirthday() const;
    void setBirthday(const QDate &newBirthday);
    QString getId() const;
    void setId(const QString &newId);
    QString getPassword() const;
    void setPassword(const QString &newPassword);
    QString getPhone_num() const;
    void setPhone_num(const QString &newPhone_num);
    int getAge() const;
    void setAge(int newAge);
    int getAttendance() const;
    void setAttendance(int newAttendance);
    int getAbsent() const;
    void setAbsent(int newAbsent);
    int getLate() const;
    void setLate(int newLate);
    int getEarly_leave() const;
    void setEarly_leave(int newEarly_leave);
    int getBe_out() const;
    void setBe_out(int newBe_out);

private:
    QString name;
    QDate birthday;
    QString id;
    QString password;
    QString phone_num;
    int age;
    int attendance;
    int absent;
    int late;
    int early_leave;
    int be_out;
};

#endif // USER_H
