#include "socketthread.h"

SocketThread::SocketThread(qintptr descriptor, QObject *parent) :
    QThread(parent), descriptor_(descriptor)
{

}

SocketThread::~SocketThread()
{
    delete socket;
}

void SocketThread::run()
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(descriptor_);
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()), Qt::DirectConnection);
    exec();
}

void SocketThread::onReadyRead()
{
    emit get_client_point(socket->readAll());
    //for HTTP response
    //QString response = "HTTP/1.1 200 OK \r\n\r\n%1";
    //socket->write(response.arg(QDateTime::currentDateTime().toString()).toUtf8());
    //socket->disconnectFromHost();
}

void SocketThread::onDisconnect()
{
    socket->close();
    quit();
}
