#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qchartview.h"

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenSerialButton_clicked();

    void ReadData();

    void on_SendButton_clicked();

    char ConvertHexChar(char ch);
    char ConvertHexToChar(char ch);

    void ParseFrame(QByteArray &msg);
    unsigned char CalFCS(QByteArray &data);//calculate fcs

    void StringToHex(QString str, QByteArray &senddata);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QChart *m_chart ;
    QLineSeries *m_series;
    QAudioInput *m_audioInput;
    XYSeriesIODevice *m_device;

};


#define SOF_STATE 0
#define LEN_STATE 1
#define CMD_STATE 2
#define DAT_STATE 3
#define FCS_STATE 4
#endif // MAINWINDOW_H
