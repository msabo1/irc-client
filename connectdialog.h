#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <mainwindow.h>
#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

private:
    irc::Client* client_;

public:
    explicit ConnectDialog(irc::Client* client, QWidget *parent = nullptr);
    ~ConnectDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
