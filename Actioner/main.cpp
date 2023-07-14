
#include <QtCore/QCoreApplication>
#include <QHostAddress>
#include <server.h>

quint16 PORT=7675;
QHostAddress IP=QHostAddress::Any;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Server server;
    server.start(IP,PORT);
    return app.exec();
}
