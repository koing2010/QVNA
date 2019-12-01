#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
/*
    Chart *chart = new Chart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(&chartView);
    //window.resize(400, 300);*/
    window.show();

    return a.exec();

}
