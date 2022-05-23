#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>

#include <boost/asio.hpp>
#include <irc-client.h>
namespace asio = boost::asio;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

    void on_channelsListWidget_itemActivated(QListWidgetItem *item);

    void on_joinChannelButton_clicked();

    void on_channelsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    asio::io_context* ctx_;
    irc::Client* client_;
    Ui::MainWindow *ui;
    std::string current_receiver_;
    std::map<std::string, std::string> histories_;

    void change_history();
};
#endif // MAINWINDOW_H
