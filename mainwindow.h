#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qchartview.h"

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QChartGlobal>
#include <QTimer>

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

    void CalImagePhase(qint32 i_acc, qint32 q_acc , double *pImage, double *pPhase);

private slots:
    void on_OpenSerialButton_clicked();

    void ReadData();

    void on_SendButton_clicked();

    char ConvertHexChar(char ch);
    char ConvertHexToChar(char ch);

    void ParseFrame(QByteArray &msg);
    unsigned char CalFCS(QByteArray &data);//calculate fcs

    void StringToHex(QString str, QByteArray &senddata);

    void Samp_timeout_handle(void);
    void SetFreq_timeout_handle(void);

    void packetCmdData(quint8 cmd, quint32 data);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QChart *m_chart ;
    QLineSeries *m_series;
    QAudioInput *m_audioInput;
    XYSeriesIODevice *m_device;
    QTimer *Samp_timer;
    QTimer *SetFreq_timer;
    quint8 SampModel;
    quint32 FrequencyStart;
    quint32 FrequencyEnd;
    quint32 FrequencyCurrent;
    quint32 FrequencySweep;

};


#define SAMPLING_ACC_NUM     4080

#define SOF_STATE 0
#define LEN_STATE 1
#define CMD_STATE 2
#define DAT_STATE 3
#define FCS_STATE 4

#define IQ_ACC_MODEL   0x00
#define ADC_NCO_MODEL   0x01

/**** parse UART CMD ******/
#define CMD_START_SAMPLING_IQ         0x01
#define CMD_START_SAMPLING_ADC        0x11
#define CMD_POLL_STATUS               0x02
#define CMD_SET_ADF_FREQ              0x03
#define CMD_SAMPLING_CLK              0x04
#define CMD_RF_PORT_and_REFLET_SW     0x05//RF -> port_1 or prot_2; p1 or p2 reflect -> ADC
#define CMD_RF_LEVEL_CTROL            0x06
#define CMD_S_PARAMETERS              0x07

#endif // MAINWINDOW_H
