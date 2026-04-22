#include "admin_window.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
/*
 * 설명: 현재 테이블의 데이터를 JSON 파일로 저장
 * param: 없음
 * return: void
 */
void Adminwindow::saveData()
{
    qDebug()<<"save Data in json...";
    QJsonArray studentArray;

    // 테이블의 모든 행을 순회하며 JSON 객체 생성
    for (int i = 0; i < studentTable->rowCount(); ++i)
    {
        QJsonObject obj;
        obj["name"] = studentTable->item(i, 0)->text();
        obj["phone"] = studentTable->item(i, 1)->text();
        obj["age"] = studentTable->item(i, 2)->text();
        obj["birth"] = studentTable->item(i, 3)->text();
        obj["id"] = studentTable->item(i, 4)->text();
        obj["pw"] = studentTable->item(i, 5)->text();
        obj["note"] = studentTable->item(i, 6)->text();

        studentArray.append(obj);
    }

    // 파일로 저장
    QJsonDocument doc(studentArray);
    QFile file("students.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}
/*
 * 설명: 저장된 JSON 파일에서 데이터를 읽어와 테이블에 로드
 */
void Adminwindow::loadData()
{
    QFile file("students.json");
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        return; // 파일이 없으면 그냥 종료
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    // 테이블에 데이터 추가
    for (const QJsonValue &value : array)
    {
        QJsonObject obj = value.toObject();
        int row = studentTable->rowCount();
        studentTable->insertRow(row);

        studentTable->setItem(row, 0, new QTableWidgetItem(obj["name"].toString()));
        studentTable->setItem(row, 1, new QTableWidgetItem(obj["phone"].toString()));
        studentTable->setItem(row, 2, new QTableWidgetItem(obj["age"].toString()));
        studentTable->setItem(row, 3, new QTableWidgetItem(obj["birth"].toString()));
        studentTable->setItem(row, 4, new QTableWidgetItem(obj["id"].toString()));
        studentTable->setItem(row, 5, new QTableWidgetItem(obj["pw"].toString()));
        studentTable->setItem(row, 6, new QTableWidgetItem(obj["note"].toString()));
    }
}