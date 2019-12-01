#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QtCore/qmath.h>
#include "qchartview.h"
#include "xyseriesiodevice.h"

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

    m_series = new QLineSeries;
        m_chart->addSeries(m_series);
        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, 2000);
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
        setLayout(mainLayout);

        QAudioFormat formatAudio;
        formatAudio.setSampleRate(8000);
        formatAudio.setChannelCount(1);
        formatAudio.setSampleSize(8);
        formatAudio.setCodec("audio/pcm");
        formatAudio.setByteOrder(QAudioFormat::LittleEndian);
        formatAudio.setSampleType(QAudioFormat::UnSignedInt);

        QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
        m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

        m_device = new XYSeriesIODevice(m_series, this);
        m_device->open(QIODevice::WriteOnly);

        m_audioInput->start(m_device);

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
    //设置波特率下拉菜单默认显示第0项
    ui->BaudBox->setCurrentIndex(0);

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
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        //设置数据位数
        switch (ui->BitBox->currentIndex())
        {
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }
        //设置校验位
        switch (ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->BitBox->currentIndex())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
        default:
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->OpenSerialButton->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
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
     /* for( int i = 0; i < TagetLen ; i ++)
        {

          bufChar[0] = ConvertHexToChar( (buf[i] >>4) & 0xF);
          bufChar[1]= ConvertHexToChar( (buf[i]& 0xF));
          bufChar[2] =' ' ;
          str += tr(bufChar);
        }
       ui->textEdit->clear();
       ui->textEdit->append(str+"X\n");*/
        /*/ cmd fomat:
                SOF  LEN  CMD  DATA  FCS
           Byte: 1    1    1    N/A   1


           e.g.: 0xFE  0x04 0x61 0x11 0x00 0x72
        */

       for( int m = 0; m < TagetLen ; m ++)
       {
         qDebug("m=%d ,buf.length()=%d , RxState =%d, buf[m] = %02X",m, TagetLen, RxState, (unsigned char)buf[m]);
         switch(RxState)
         {
         case SOF_STATE:
             if(buf[m] == (char)0xFE)
              {
              RxState = LEN_STATE;
              Lenth = 0;
              Lenth_token = 0;

              qDebug(" SOF_STATE \n");

             }
               Rxbuf.clear();
             break;
         case LEN_STATE:
             Lenth_token = buf[m];
             RxState = CMD_STATE;

             qDebug(" LEN_STATE \n");
             break;
         case CMD_STATE:
             Rxbuf[0] = Lenth_token;
             Rxbuf[1] = buf[m];//get the cmd
             Lenth = 2;
             Rxbuf.resize(Lenth_token);
             if( Lenth_token != 0 && Lenth_token < 10)
             {
               RxState = DAT_STATE;
               qDebug(" CMD_STATE \n");
             }
             else
             {
               RxState = SOF_STATE;
             }

             break;
         case DAT_STATE:
             Rxbuf[Lenth] = (char)buf[m];
             Lenth ++;

             if(Lenth >= Lenth_token)
             {
              RxState = FCS_STATE;
             }

             qDebug(" DAT_STATE \n");
             break;
         case FCS_STATE:
             qDebug(" FCS_STATE \n");

              qDebug(" CalFCS =%02X \n", CalFCS(Rxbuf));
             if(buf[m] == (char)CalFCS(Rxbuf))
             {
               //parse the frame
                 ParseFrame(Rxbuf);
             }




             RxState =SOF_STATE;
             Lenth = 0;
             Lenth_token = 0;
             Rxbuf.clear();
            break;

          default:
            RxState =SOF_STATE;
            break;

         }
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
