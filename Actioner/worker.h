#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QtNetwork>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QTcpSocket *socket, QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void process();
    void readData();
private:
   QTcpSocket *socket;

};

#endif // WORKER_H
