#include "tcpserver.h"

tcpServer::tcpServer()
{
    qDebug() << Q_FUNC_INFO;

//    connect(this, &QTcpServer::newConnection, this, &tcpServer::newClientConnection);

    if(this->listen(QHostAddress::Any, 12345))
    {
        qDebug() << "Server started: " << this->serverAddress() << this->serverPort();
    }
    else
    {
        qDebug() << "Server didn't start: " << this->serverError();
    }
}

void tcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << Q_FUNC_INFO << socketDescriptor;

    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->setSocketDescriptor(socketDescriptor);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &tcpServer::readyReadTCPClient);//whenever new data comes to tcpSocket this function is going to be called
    connect(tcpSocket, &QTcpSocket::disconnected, this, &tcpServer::disconnectedTCPClient);//whenever tcpSocket Disconnects

    addNewConnectedClient(tcpSocket);
}

void tcpServer::addNewConnectedClient(QTcpSocket *tcpSocket)
{
    qDebug() << Q_FUNC_INFO;
    socketsSet_ << tcpSocket;
}

void tcpServer::removeDisconnectedClient(QTcpSocket *tcpSocket)
{
    qDebug() << Q_FUNC_INFO << socketsSet_.remove(tcpSocket);
}

void tcpServer::sendMessages(const QByteArray& data)
{
    qDebug() << Q_FUNC_INFO;
    QSetIterator<QTcpSocket *> i(socketsSet_);
    while (i.hasNext())
        i.next()->write(data);
}

void tcpServer::readyReadTCPClient()
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(sender());
    if(tcpSocket == 0)
    {
        qDebug() << "ERROR WRONG TCP SOCKET POINTER";
        return;
    }

    qDebug() << " TCP = " <<tcpSocket->peerAddress() << tcpSocket->peerPort() << tcpSocket;

    QByteArray data = tcpSocket->readAll();

    sendMessages(data);

    qDebug() << data;
}

void tcpServer::disconnectedTCPClient()
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << tcpSocket;
    removeDisconnectedClient(tcpSocket);

    qWarning() << "Client disconnected :" << tcpSocket->peerAddress().toString() << tcpSocket->peerPort();

    tcpSocket->deleteLater();
}

//void tcpServer::newClientConnection()
//{
//    qDebug() << Q_FUNC_INFO;
//    QTcpSocket *tcpSocket = nextPendingConnection();

//    connect(tcpSocket, &QTcpSocket::readyRead, this, &tcpServer::readyReadTCPClient);//whenever new data comes to tcpSocket this function is going to be called
//    connect(tcpSocket, &QTcpSocket::disconnected, this, &tcpServer::disconnectedTCPClient);//whenever tcpSocket Disconnects

//    addNewConnectedClient(tcpSocket);
//}
