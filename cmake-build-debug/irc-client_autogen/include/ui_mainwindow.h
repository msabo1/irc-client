/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *chatHistoryTextEdit;
    QPushButton *sendButton;
    QLineEdit *newMessageLineEdit;
    QListWidget *channelsListWidget;
    QLineEdit *joinChannelLineEdit;
    QPushButton *joinChannelButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1176, 643);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        chatHistoryTextEdit = new QTextEdit(centralwidget);
        chatHistoryTextEdit->setObjectName(QString::fromUtf8("chatHistoryTextEdit"));
        chatHistoryTextEdit->setEnabled(false);
        chatHistoryTextEdit->setGeometry(QRect(240, 10, 721, 491));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(880, 510, 80, 25));
        newMessageLineEdit = new QLineEdit(centralwidget);
        newMessageLineEdit->setObjectName(QString::fromUtf8("newMessageLineEdit"));
        newMessageLineEdit->setGeometry(QRect(240, 510, 611, 25));
        channelsListWidget = new QListWidget(centralwidget);
        channelsListWidget->setObjectName(QString::fromUtf8("channelsListWidget"));
        channelsListWidget->setGeometry(QRect(0, 60, 231, 471));
        joinChannelLineEdit = new QLineEdit(centralwidget);
        joinChannelLineEdit->setObjectName(QString::fromUtf8("joinChannelLineEdit"));
        joinChannelLineEdit->setGeometry(QRect(10, 30, 171, 25));
        joinChannelButton = new QPushButton(centralwidget);
        joinChannelButton->setObjectName(QString::fromUtf8("joinChannelButton"));
        joinChannelButton->setGeometry(QRect(190, 30, 37, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1176, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        chatHistoryTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        joinChannelButton->setText(QCoreApplication::translate("MainWindow", "Join", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
