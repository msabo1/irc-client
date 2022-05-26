#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <boost/asio.hpp>
#include <utility>
#include <QTimer>
#include <connectdialog.h>


namespace asio = boost::asio;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctx_ = new asio::io_context();
    client_ = new irc::Client(*ctx_, irc::Settings{});
    auto *connect_dialog = new ConnectDialog(client_, this);
    connect_dialog->show();
}

MainWindow::~MainWindow()
{
    delete ctx_;
    delete client_;
    delete ui;
}

void MainWindow::connect_to_server(std::string server, std::string port, std::string nick){
    client_->set_settings(irc::Settings{server, port, nick});
    client_->connect();
    current_receiver_ = "lobby";
    client_->set_on_message_received_handler([this](irc::Response response) {
        auto delimiter_pos = response.params.find(' ');
        auto receiver = response.params.substr(0, delimiter_pos);
        auto history = receiver.find('#') == 0 ? receiver : response.sender;
        histories_[history] += response.sender + ": " + response.params.substr(delimiter_pos) + "\r\n";
        if(history == current_receiver_){
            ui->chatHistoryTextBrowser->setText(QString::fromStdString(histories_[history]));
        }else{
            auto items = ui->activeChatsListWidget->findItems(QString::fromStdString(history), Qt::MatchStartsWith);
            if(!items.isEmpty()){
                items.front()->setText(QString::fromStdString(history + "(*)"));
            }else{
                ui->activeChatsListWidget->addItem(QString::fromStdString(history + "(*)"));
            }

        }
    });

    client_->set_on_names_received_handler([this](irc::Response response){
        auto names = QString::fromStdString(response.params).split(QString::fromStdString(":"))[1];
        ui->namesListWidget->clear();
        for(auto name : names.split(" ")){
            ui->namesListWidget->addItem(name);
        }
    });
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){ctx_->poll();});
    timer->start();
}

void MainWindow::on_sendButton_clicked()
{
    auto message = ui->newMessageLineEdit->text();
    histories_[current_receiver_] += "You: " + message.toStdString() + "\r\n";
    client_->send_private_message(message.toStdString(), current_receiver_);
    ui->chatHistoryTextBrowser->setText(QString::fromStdString(histories_[current_receiver_]));
    ui->newMessageLineEdit->clear();
}

void MainWindow::on_joinChannelButton_clicked()
{
    auto channel = ui->joinChannelLineEdit->text();
    client_->join(channel.toStdString());
    ui->joinChannelLineEdit->clear();
    ui->activeChatsListWidget->addItem(channel);
    ui->activeChatsListWidget->setCurrentRow(ui->activeChatsListWidget->count() -1);
}


void MainWindow::change_receiver(QString receiver){
    current_receiver_ = receiver.toStdString();
    client_->send_names_command(current_receiver_);
    ui->chatHistoryTextBrowser->setText(QString::fromStdString(histories_[current_receiver_]));
}

void MainWindow::on_namesListWidget_itemClicked(QListWidgetItem *item)
{
    auto nick = item->text().startsWith("@") ? item->text().right(item->text().length() - 1) : item->text();
    auto active_chats = ui->activeChatsListWidget->findItems(nick, Qt::MatchStartsWith);
    if(active_chats.length() > 0){
        ui->activeChatsListWidget->setCurrentItem(active_chats.front());
        active_chats.front()->setSelected(true);
        return;
    }
    ui->activeChatsListWidget->addItem(nick);
    ui->activeChatsListWidget->setCurrentRow(ui->activeChatsListWidget->count() -1);
}


void MainWindow::on_activeChatsListWidget_itemClicked(QListWidgetItem *item)
{
    if(item->text().endsWith(QString::fromStdString("(*)"))){
        item->setText(item->text().left(item->text().length()-3));
    }
    change_receiver(item->text());
}


void MainWindow::on_activeChatsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current->text().endsWith(QString::fromStdString("(*)"))){
        current->setText(current->text().left(current->text().length()-3));
    }
    change_receiver(current->text());
}

