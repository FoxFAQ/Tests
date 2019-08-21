#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    tcpSocket_ = new QTcpSocket(this);

    connect(tcpSocket_, &QTcpSocket::readyRead, this, &MainWindow::readyRead);//whenever new data comes to tcpSocket this function is going to be called
    connect(tcpSocket_, &QTcpSocket::connected, this, &MainWindow::connected);//whenever tcpSocket Connects
    connect(tcpSocket_, &QTcpSocket::disconnected, this, &MainWindow::disconnected);//whenever tcpSocket Disconnects
}

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
    delete ui;
}

void MainWindow::readyRead()
{
    qDebug() << Q_FUNC_INFO;

    QByteArray data = tcpSocket_->readAll();

    ui->plainTextEditHistory->appendPlainText(data);
}

void MainWindow::connected()
{
    qDebug() << Q_FUNC_INFO;
    ui->plainTextEditHistory->appendPlainText("Connected to " + ui->lineEditIpPort->text());
    ui->pushButtonConnectToServer->setEnabled(false);
    ui->lineEditIpPort->setEnabled(false);
}

void MainWindow::disconnected()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::socketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << Q_FUNC_INFO;

    QString strError =
            "Error: " + (socketError == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         socketError == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         socketError == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(tcpSocket_->errorString())
                        );
    ui->plainTextEditHistory->appendPlainText(strError);
}

void MainWindow::on_pushButtonConnectToServer_clicked()
{
    qDebug() << Q_FUNC_INFO;

    QStringList ipPort = ui->lineEditIpPort->text().split(':', QString::SkipEmptyParts);

    if(ipPort.size() == 2)
    {
        tcpSocket_->connectToHost(ipPort.at(0), ipPort.at(1).toInt());
        if(!tcpSocket_->waitForConnected(1000))
            ui->plainTextEditHistory->appendPlainText("Couldn't connect to: " + ui->lineEditIpPort->text());
    }
    else
    {
        ui->plainTextEditHistory->appendPlainText("Wrong IP/port?");
    }
}

void MainWindow::on_pushButtonSendMessage_clicked()
{
    qDebug() << Q_FUNC_INFO;

    if(tcpSocket_->write(ui->lineEditMessage->text().toLocal8Bit()) == -1)
        ui->plainTextEditHistory->appendPlainText("Error sending the message");
    ui->lineEditMessage->clear();
}
