#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Statuswindow; }
QT_END_NAMESPACE

class Statuswindow : public QWidget
{
    Q_OBJECT

public:
    explicit Statuswindow(QWidget *parent = nullptr);
    ~Statuswindow();

private:
    Ui::Statuswindow *ui;
    void setupChart(); // 차트 생성 함수
};

#endif // STATUSWINDOW_H