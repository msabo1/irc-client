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
    void connect_to_server(std::string server, std::string port, std::string nick);



private slots:
    void on_sendButton_clicked();

    void on_joinChannelButton_clicked();

    void on_namesListWidget_itemClicked(QListWidgetItem *item);

    void on_activeChatsListWidget_itemClicked(QListWidgetItem *item);

    void on_activeChatsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    asio::io_context* ctx_;
    irc::Client* client_;
    Ui::MainWindow *ui;
    std::string current_receiver_;
    std::map<std::string, std::string> histories_;

    void change_receiver(QString receiver);
};
#endif // MAINWINDOW_H
