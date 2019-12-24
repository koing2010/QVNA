/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qchartview.h>
#include <usercombox.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_3;
    UserComBox *PortBox;
    QComboBox *ModelSelBox;
    QPushButton *OpenSerialButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *SendButton;
    QTextEdit *Damping;
    QLabel *label_5;
    QChartView *WavDispGraph;
    QLabel *label_2;
    QComboBox *RF_PortS;
    QLabel *label_4;
    QComboBox *SweepBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1048, 829);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(2, 23, 48, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(12, 82, 30, 16));
        PortBox = new UserComBox(centralWidget);
        PortBox->setObjectName(QStringLiteral("PortBox"));
        PortBox->setGeometry(QRect(56, 23, 69, 19));
        ModelSelBox = new QComboBox(centralWidget);
        ModelSelBox->setObjectName(QStringLiteral("ModelSelBox"));
        ModelSelBox->setGeometry(QRect(56, 50, 92, 20));
        OpenSerialButton = new QPushButton(centralWidget);
        OpenSerialButton->setObjectName(QStringLiteral("OpenSerialButton"));
        OpenSerialButton->setGeometry(QRect(10, 160, 71, 23));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(200, 20, 301, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(510, 20, 221, 31));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(750, 20, 75, 31));
        Damping = new QTextEdit(centralWidget);
        Damping->setObjectName(QStringLiteral("Damping"));
        Damping->setGeometry(QRect(880, 30, 104, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(890, 10, 71, 16));
        WavDispGraph = new QChartView(centralWidget);
        WavDispGraph->setObjectName(QStringLiteral("WavDispGraph"));
        WavDispGraph->setGeometry(QRect(100, 130, 931, 671));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(2, 50, 48, 16));
        RF_PortS = new QComboBox(centralWidget);
        RF_PortS->setObjectName(QStringLiteral("RF_PortS"));
        RF_PortS->setGeometry(QRect(170, 80, 56, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 80, 31, 16));
        SweepBox = new QComboBox(centralWidget);
        SweepBox->setObjectName(QStringLiteral("SweepBox"));
        SweepBox->setGeometry(QRect(49, 81, 56, 20));
        MainWindow->setCentralWidget(centralWidget);
        label->raise();
        label_3->raise();
        PortBox->raise();
        ModelSelBox->raise();
        SweepBox->raise();
        OpenSerialButton->raise();
        textEdit->raise();
        textEdit_2->raise();
        SendButton->raise();
        Damping->raise();
        label_5->raise();
        WavDispGraph->raise();
        label_2->raise();
        SweepBox->raise();
        SweepBox->raise();
        RF_PortS->raise();
        label_4->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1048, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243    ", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "SWEEP", Q_NULLPTR));
        ModelSelBox->clear();
        ModelSelBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "IQ_ACC\346\225\260\346\215\256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "ADC_NCO\346\225\260\346\215\256", Q_NULLPTR)
        );
        OpenSerialButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        SendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", Q_NULLPTR));
        Damping->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\250\241\345\274\217\351\200\211\346\213\251", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\250\241\345\274\217\351\200\211\346\213\251", Q_NULLPTR));
        RF_PortS->clear();
        RF_PortS->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "S11", Q_NULLPTR)
         << QApplication::translate("MainWindow", "S12", Q_NULLPTR)
         << QApplication::translate("MainWindow", "S21", Q_NULLPTR)
         << QApplication::translate("MainWindow", "S22", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", Q_NULLPTR));
        SweepBox->clear();
        SweepBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "10MHz", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1MHz", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2MHz", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4MHz", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5MHz", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
