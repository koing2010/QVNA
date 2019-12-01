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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *PortBox;
    QComboBox *BaudBox;
    QComboBox *BitBox;
    QComboBox *ParityBox;
    QLabel *label_4;
    QLabel *label_6;
    QComboBox *StopBox;
    QPushButton *OpenSerialButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *SendButton;
    QTextEdit *Damping;
    QLabel *label_5;
    QChartView *WavDispGraph;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(651, 626);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 130, 54, 12));
        PortBox = new QComboBox(centralWidget);
        PortBox->setObjectName(QStringLiteral("PortBox"));
        PortBox->setGeometry(QRect(60, 50, 69, 22));
        BaudBox = new QComboBox(centralWidget);
        BaudBox->setObjectName(QStringLiteral("BaudBox"));
        BaudBox->setGeometry(QRect(60, 90, 69, 22));
        BitBox = new QComboBox(centralWidget);
        BitBox->setObjectName(QStringLiteral("BitBox"));
        BitBox->setGeometry(QRect(60, 120, 69, 22));
        ParityBox = new QComboBox(centralWidget);
        ParityBox->setObjectName(QStringLiteral("ParityBox"));
        ParityBox->setGeometry(QRect(60, 160, 69, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 160, 61, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 200, 54, 12));
        StopBox = new QComboBox(centralWidget);
        StopBox->setObjectName(QStringLiteral("StopBox"));
        StopBox->setGeometry(QRect(60, 200, 69, 22));
        OpenSerialButton = new QPushButton(centralWidget);
        OpenSerialButton->setObjectName(QStringLiteral("OpenSerialButton"));
        OpenSerialButton->setGeometry(QRect(60, 240, 71, 23));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(200, 20, 301, 101));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(200, 160, 221, 31));
        SendButton = new QPushButton(centralWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(430, 160, 75, 31));
        Damping = new QTextEdit(centralWidget);
        Damping->setObjectName(QStringLiteral("Damping"));
        Damping->setGeometry(QRect(520, 50, 104, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(520, 30, 71, 16));
        WavDispGraph = new QChartView(centralWidget);
        WavDispGraph->setObjectName(QStringLiteral("WavDispGraph"));
        WavDispGraph->setGeometry(QRect(200, 210, 361, 351));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 651, 23));
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
        label->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        BaudBox->clear();
        BaudBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "38400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "57600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
        );
        BitBox->clear();
        BitBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        ParityBox->clear();
        ParityBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        StopBox->clear();
        StopBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
        );
        OpenSerialButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        SendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\345\211\215\347\275\256\350\241\260\345\207\217db", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
