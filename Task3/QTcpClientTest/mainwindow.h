#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readyRead();
    void connected();
    void disconnected();
    void socketError(QAbstractSocket::SocketError socketError);

    void on_pushButtonConnectToServer_clicked();

    void on_pushButtonSendMessage_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *tcpSocket_;
};

#endif // MAINWINDOW_H
