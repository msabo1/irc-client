#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <boost/asio.hpp>
#include <utility>
#include <QTimer>


namespace asio = boost::asio;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctx_ = new asio::io_context();
    client_ = new irc::Client(*ctx_, irc::Settings{"hostsailor.ro.quakenet.org", "6667", "marac2"});
    current_receiver_ = "lobby";
    client_->set_on_line_received_handler([this](std::string line){
        histories_[current_receiver_] += line;
      ui->chatHistoryTextEdit->setText(QString::fromStdString(histories_[current_receiver_]));
    });
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){ctx_->poll();});
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ctx_;
    delete client_;
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    auto message = ui->newMessageLineEdit->text();
    histories_[current_receiver_] += "You: " + message.toStdString() + "\r\n";
    client_->send_private_message(message.toStdString(), current_receiver_);
    ui->newMessageLineEdit->clear();
}


void MainWindow::on_channelsListWidget_itemActivated(QListWidgetItem *item)
{
    current_receiver_ = item->text().toStdString();
}


void MainWindow::on_joinChannelButton_clicked()
{
    auto channel = ui->joinChannelLineEdit->text();
    client_->join(channel.toStdString());
    ui->joinChannelLineEdit->clear();
    ui->channelsListWidget->addItem(channel);
    ui->channelsListWidget->setCurrentRow(ui->channelsListWidget->count() -1);
}


void MainWindow::on_channelsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    current_receiver_ = current->text().toStdString();
    change_history();
}

void MainWindow::change_history(){
    ui->chatHistoryTextEdit->setText(QString::fromStdString(histories_[current_receiver_]));
}

