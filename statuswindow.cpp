#include "statuswindow.h"
#include "ui_statuswindow.h"
#include <QtCharts/QChart>

Statuswindow::Statuswindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Statuswindow)
{
    ui->setupUi(this);

    // 1. 진도율 설정
    ui->progressBar->setRange(0, 110);
    ui->progressBar->setValue(92);
    ui->progressBar->setFormat("%v / %m 일");

    // 2. 출결 수치 설정
    ui->lbl_attendance->setText("85");
    ui->lbl_tardy->setText("3");
    ui->lbl_early->setText("2");
    ui->lbl_out->setText("1");
    ui->lbl_absence->setText("5");

    // 3. 차트 생성
    setupChart();
}

void Statuswindow::setupChart()
{
    // 데이터 설정
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    series->append("출석", 85);
    series->append("지각", 3);
    series->append("결석", 5);

    // 차트 외관 설정
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("출결 통계");
    chart->legend()->setAlignment(Qt::AlignBottom); // 범례 위치 설정
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // widget_chart (Qt Designer에서 배치한 위젯)에 차트 뷰 배치
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // 부드러운 그래픽

    // 레이아웃이 없을 경우 생성하여 차트뷰 추가
    if (!ui->widget_chart->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->widget_chart);
        layout->setContentsMargins(0, 0, 0, 0); // 여백 제거
        layout->addWidget(chartView);
    }
}

Statuswindow::~Statuswindow()
{
    delete ui;
}