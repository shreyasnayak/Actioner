#include "server.h"
#include <QJsonDocument>
Server::Server(QObject *parent) : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::handleNewConnection);
}

void Server::start(QHostAddress address,quint16 &port)
{
    if (!server->listen(address, port))
    {
       qCritical() << QString("Failed to start server %1").arg(server->errorString());
        return;
    }
    qInfo() << QString("Server started, listening on port %1").arg(server->serverPort());
}

void Server::handleNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::handleReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::handleDisconnected);
    qDebug() << "New client connected :" << clientSocket->peerAddress().toString() << clientSocket->peerPort();
}

void Server::handleReadyRead()
{
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
        if (!clientSocket)
            return;

        /* Read all the data from client */
        QByteArray requestData = clientSocket->readAll();
        QJsonDocument jsonMessage = QJsonDocument::fromJson(requestData);
        QJsonObject processedJsonMessage = jsonMessage.object();
        if(processedJsonMessage.isEmpty())
        {
            qWarning() << QString("Failed to read json message");
        }
        else
        {
            qDebug() << QString("Received data from client %1 ").arg(QString::fromUtf8(jsonMessage.toJson(QJsonDocument::JsonFormat::Compact)));
            emit messageFromClient(processedJsonMessage,clientSocket);
        }

}
void Server::handleDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    qDebug() << QString("Client disconnected from %1:%2 ").arg(clientSocket->peerAddress().toString(),clientSocket->peerPort());
    clientSocket->deleteLater();
}
