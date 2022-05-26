#include "connectdialog.h"
#include "ui_connectdialog.h"



ConnectDialog::ConnectDialog(irc::Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    client_(client)
{
    ui->setupUi(this);
    client_->set_on_connection_failed_handler([this]{
        ui->errorLabel->setText("Connection failed, try again");
    });
    client_->set_on_connection_success_handler([this]{
        accept();
    });
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_pushButton_clicked()
{
    ((MainWindow*)parent())->connect_to_server(ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString(), ui->lineEdit_3->text().toStdString());

}

