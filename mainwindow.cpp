#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QtCore/qmath.h>
#include "qchartview.h"
#include "xyseriesiodevice.h"
#include <qdebug.h>
#include "math.h"

#include <QtCharts>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>

using namespace QtCharts;
QT_CHARTS_USE_NAMESPACE

unsigned char RxState = SOF_STATE;
unsigned int Lenth_token = 0;
unsigned int Lenth = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chart = new QChart;
    ui->WavDispGraph->setChart(m_chart);

    SampModel = IQ_ACC_MODEL;

    m_series = new QLineSeries;
        m_chart->addSeries(m_series);
        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, 960);
        axisX->setLabelFormat("%g");
        axisX->setTitleText("Samples");
        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(-1, 1);
        axisY->setTitleText("Audio level");
        m_chart->setAxisX(axisX, m_series);
        m_chart->setAxisY(axisY, m_series);
        m_chart->legend()->hide();
        m_chart->setTitle("Data from the microphone");

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(ui->WavDispGraph);
        //setLayout(mainLayout);


        m_device = new XYSeriesIODevice(m_series, this);
        m_device->open(QIODevice::WriteOnly);

        //m_device->SetRefreshRate(2);


    //查找可用的串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打卡串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(10000000);
        //设置数据位数
        serial->setDataBits(QSerialPort::Data8);
        //设置校验位
         serial->setParity(QSerialPort::NoParity);
        //设置停止位
         serial->setStopBits(QSerialPort::OneStop);
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->ModelSelBox->setEnabled(false);
        ui->BitBox->setEnabled(false);

        ui->OpenSerialButton->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);

        //采样定时器
        Samp_timer = new QTimer();

        //连接定时器信号和处理方法
        QObject::connect(Samp_timer,&Samp_timer->timeout,this,&MainWindow::Samp_timeout_handle);


        //设定频率寄存器
        SetFreq_timer = new QTimer();
        QObject::connect(SetFreq_timer,&SetFreq_timer->timeout,this,&MainWindow::SetFreq_timeout_handle);
        SetFreq_timer ->start(20);
        FrequencyStart = 140;//初始化 为140MHz
        FrequencyEnd = 4400;//4.4g
        FrequencyCurrent = FrequencyStart;
        FrequencySweep = 10;

        //读取模式
        if( ui->ModelSelBox->currentText()== tr("IQ_ACC数据") )
          {
              SampModel = IQ_ACC_MODEL;
          }
        else if( ui->ModelSelBox->currentText()== tr("ADC_NCO数据") )
          {
              SampModel = ADC_NCO_MODEL;
          }

        //启动定时器
         if(SampModel == ADC_NCO_MODEL)// 显示ADC的数据
             Samp_timer->start(50);
         //else
         //    Samp_timer->start(10);// FPGA 内部计算IQ值


    }
    else
    {
        //先关闭定时器
          SetFreq_timer->stop();
        //关闭采样定时
          Samp_timer->stop();

        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ModelSelBox->setEnabled(true);
        ui->OpenSerialButton->setText(tr("打开串口"));



    }




}
//读取接收到的信息
void MainWindow::ReadData()
{
    QByteArray buf;
    QByteArray Rxbuf;
    QByteArray bufChar;
     buf = serial->readAll();
    //QString str = ui->textEdit->toPlainText();
    int TagetLen = 0;
    if(!buf.isEmpty())
     {
        TagetLen = buf.length();
          //str+=tr(buf);
        Lenth_token += TagetLen;
        qDebug("buf.length()=%d   token = %d",TagetLen, Lenth_token);

        if(SampModel == ADC_NCO_MODEL)// 显示ADC的数据
          {

             if(Lenth_token>=7680)
             {
                 Lenth_token = 0;

             }

             //显示数据
            m_device->writeData(buf,TagetLen);
          }
        else if(TagetLen == 16)
          {

            qint32 IF_I_ACC_F, IF_Q_ACC_F;
            qint32 IF_I_ACC_R, IF_Q_ACC_R;
            double Image_F, Phase_F;
            double Image_R, Phase_R;

            memcpy(&IF_I_ACC_F, &buf.data()[0], sizeof(qint32));
            memcpy(&IF_Q_ACC_F, &buf.data()[4], sizeof(qint32));

            CalImagePhase(IF_I_ACC_F, IF_Q_ACC_F, &Image_F, &Phase_F);//根据ACC 计算出幅度和相位

            memcpy(&IF_I_ACC_R, &buf.data()[8], sizeof(qint32));
            memcpy(&IF_Q_ACC_R, &buf.data()[12], sizeof(qint32));


            CalImagePhase(IF_I_ACC_R, IF_Q_ACC_R, &Image_R, &Phase_R);//根据ACC 计算出幅度和相位
            m_device->writeFloatData(Image_F);
          }




      }
    buf.clear();
}

//发送按钮槽函数
void MainWindow::on_SendButton_clicked()
{
    QString dataStr = ui->textEdit_2->toPlainText().toLatin1();
/*    if(dataStr.length() %2 )//发送为奇数个 在落单字符前面加一个0
    {
        dataStr.insert(dataStr.length() -1, '0');
    }*/
    QByteArray sendData;
    StringToHex(dataStr, sendData);
    serial->write(sendData);
}


char MainWindow::ConvertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
           return ch - '0';
       else if ((ch >= 'A') && (ch <= 'F'))
           return ch - 'A' + 10;
       else if ((ch >= 'a') && (ch <= 'f'))
           return ch - 'a' + 10;
       else return ch -  ch;


}
char MainWindow::ConvertHexToChar(char ch)
{
     if ((ch >= 0) && (ch <= 9))
     {

        return (ch + 0x30);
     }
     else if( ch > 9 && ch < 16 )
     {

         return ch -10 + 'A';
     }
     else
     {
         return '*';
     }
}
void MainWindow:: StringToHex(QString str, QByteArray &senddata)
{

    int hexdata,lowhexdata;
      int hexdatalen = 0;
      int len = str.length();
      senddata.resize(len / 2);
      char lstr,hstr;
      for (int i = 0; i < len; ) {
          hstr = str[i].toLatin1();
          if (hstr == ' ') {
              ++i;
              continue;
          }
          ++i;
          if (i  >= len) break;
          lstr = str[i].toLatin1();
          hexdata = ConvertHexChar(hstr);
          lowhexdata = ConvertHexChar(lstr);
          if ((hexdata == 16) || (lowhexdata == 16))
              break;
          else
              hexdata = hexdata*16 + lowhexdata;
          ++i;
          senddata[hexdatalen] = (char)hexdata;
          ++hexdatalen;
      }
      senddata.resize(hexdatalen);

}
//数据祯处理
void MainWindow::ParseFrame(QByteArray &msg)
{
    /*/ cmd fomat:
             LEN  CMD  DATA
       Byte:  1    1    N/A


       e.g.:  0x02 0x61 0x11 0x00
    */
    QString BufString;
    QString str = ui->textEdit->toPlainText();
    double  ReduceDB = ui->Damping->toPlainText().toDouble();
    //QByteArray bufChar;
    unsigned int adc_value = 0;

    //AD8307 dB meter
   if((msg[0] == (char)0x08) && (msg[1] == (char)0x81) ) // CMD_RSP = CMD_REQ | 0x80;
   {
       //lenth = 6: byte[2:3] = rev_voltage 10mv uint ; byte[4:5] = ADC_CH1 and  byte[6:7]=ADC_CH2
       //display the dBm
       adc_value = ((unsigned char)msg[4]+(unsigned char)msg[5]*256);
        double pwr = adc_value*3327.0/(4096.0* 25.0) -85.44 +1.5;//校准40mv +1.6db

       //Qt中求指数,通过qPow(qreal x, qreal y),相当于x的y次方。y是指数
       pwr=  pwr + ReduceDB;
       BufString.sprintf("%4.1fmV,  %4.1f dBm, %5.1f mW\n",adc_value*3327.0/4096.0+40,pwr , qPow(10, pwr/10));
   }


  //AD8302 VNA
   if((msg[0] == (char)0x08) && (msg[1] == (char)0x82) ) // CMD_RSP = CMD_REQ | 0x80;
   {
       //lenth = 6: byte[2:3] = rev_voltage 10mv uint ; byte[4:5] = ADC_CH3 and  byte[6:7]=ADC_CH4
       //display the dBm
       adc_value = ((unsigned char)msg[4]+(unsigned char)msg[5]*256);
        double Vphs = adc_value*3327.0/(4096.0); //VHPS

       adc_value = ((unsigned char)msg[6]+(unsigned char)msg[7]*256);
        double Vmage = adc_value*3327.0/(4096.0); //VMAGE

       //Qt中求指数,通过qPow(qreal x, qreal y),相当于x的y次方。y是指数

       BufString.sprintf("Vphs= %4.1fmV, VMAGE=%4.1fmV\n",Vphs, Vmage);
        str += BufString;
       double t = qPow(10,(Vmage+40-1178)/(30*20));
       BufString.sprintf("Angle= %4.1f °, Mage =%4.2f, Rl=%4.2f oh\n",180-(Vphs)/10,t, 50*(1+t)/(1-t) );
   }

   // display update
   str += BufString;
   ui->textEdit->clear();
   ui->textEdit->append(str);
}

//按位异或校验
unsigned char MainWindow::CalFCS(QByteArray &data)
{

      int x;
      unsigned char xorResult;

      xorResult = 0;

      for ( x = 0; x <  data.size(); x++ )
      {

        xorResult = (unsigned char)xorResult ^ (unsigned char)data[x];
      }

      return (unsigned char)xorResult;
}
/*******************************************************
定时采样
*/
void MainWindow::Samp_timeout_handle(void)
{
  if(SampModel == ADC_NCO_MODEL)
    {
       packetCmdData(CMD_START_SAMPLING_ADC, 0);
    }
   else if(SampModel == IQ_ACC_MODEL)
    {
      packetCmdData(CMD_START_SAMPLING_IQ, 0);

      Samp_timer->stop();
      SetFreq_timer->start(10);
    }
}
/******************************************************

*/
void MainWindow::SetFreq_timeout_handle(void)
{
  SetFreq_timer->stop();

  packetCmdData(CMD_SET_ADF_FREQ, FrequencyCurrent*1000 );
  Sleep(10);
  Samp_timer->start(10);

  FrequencyCurrent = FrequencyCurrent + FrequencySweep;
  if(FrequencyCurrent > FrequencyEnd)
    {
      FrequencyCurrent = FrequencyStart;
    }
  qDebug("FreqCurrent %d",FrequencyCurrent );
}

/********************************************************
packet data 打包发送数据
*/
void MainWindow::packetCmdData(quint8 cmd, quint32 data)
{
    char buf[4];
    QByteArray sendData;
    sendData[0] = 0xFE;
    sendData[1] = cmd;
    memcpy(buf, &data, sizeof(quint32));
    sendData.append(buf);
    serial->write(sendData);


}
/*******************************************************
 累计和 计算出 幅度 和 相位
*/
void MainWindow::CalImagePhase(qint32 i_acc, qint32 q_acc,double *pImage, double *pPhase)
{

    double Phase= qAtan(q_acc / i_acc);//结果是弧度

    double Image = qFabs(i_acc * 2 / qCos(Phase) / SAMPLING_ACC_NUM / 0x20000);//常数是跟累计器的累计个数有关系

    *pImage = Image;

     Phase = Phase / M_PI * 180; //弧度 转成角度

     if (q_acc >= 0 && i_acc >= 0)
         *pPhase = Phase;
     else if (q_acc >= 0 && i_acc < 0)
         *pPhase = 180 + Phase;
     else if (q_acc < 0 && i_acc >= 0)
         *pPhase = 360 + Phase;
     else
         *pPhase = 180 + Phase;

}
