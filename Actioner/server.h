#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
/**
 * @brief The Server class is designed to handle json message from TCP socket
 */

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void start();
signals:
    void messageFromClient(QJsonObject &jsonMessage,QTcpSocket *clientSocket);
private slots:
    void handleNewConnection();
    void handleReadyRead();
    void handleDisconnected();
private:
    QTcpServer *server;
};
#endif // SERVER_H


