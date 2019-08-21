#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QSet>

class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpServer();

protected:
    virtual void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

signals:

private:
    QSet<QTcpSocket *> socketsSet_;
    void addNewConnectedClient(QTcpSocket *tcpSocket);
    void removeDisconnectedClient(QTcpSocket *tcpSocket);
    void sendMessages(const QByteArray &data);

private slots:
    void readyReadTCPClient();
    void disconnectedTCPClient();
//    void newClientConnection();
};

#endif // TCPSERVER_H
