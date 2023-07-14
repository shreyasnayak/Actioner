#include "worker.h"

Worker::Worker(QTcpSocket *socket, QObject *parent) : QObject{parent} , socket(socket)
{

}

void Worker::process()
{
    qDebug() << "New connection from:" << socket->peerAddress().toString();
    connect(socket, &QTcpSocket::readyRead, this, &Worker::readData);
}

void Worker::readData()
{
    QByteArray data = socket->readAll();
    socket->write(data);  // Echo back the data

    if (data == "quit\n")
    {
        socket->disconnectFromHost();
        emit finished();
    }
}
