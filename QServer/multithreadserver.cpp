#include "multithreadserver.h"
#include "socketthread.h"

MultiThreadServer::MultiThreadServer(QObject *parent) :
    QTcpServer(parent)
{

}

PortValid MultiThreadServer::setPortNumber(const std::string &port)
{
    int socketPort = 0;
    for(auto item : port){
        if(isdigit(item)){
            socketPort *= 10;
            socketPort += item - '0';
        }
        else break;
    }
    if(socketPort > 0 && socketPort < 65535){
        this->port = socketPort;
        return PortValid::CORRECT;
    }
    return PortValid::INCORRECT;
}

void MultiThreadServer::incomingConnection(qintptr handle)
{
    emit send_to_mainwindow("New connection.");
    SocketThread* thread = new SocketThread(handle);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(get_client_point(const QString&)), this, SLOT(get_request(const QString&)));
    thread->start();
}

void MultiThreadServer::run(const QString& port)
{
    switch(setPortNumber(port.toStdString())){
    case PortValid::CORRECT:
        if(listen(QHostAddress::Any, this->port)){
            emit send_to_mainwindow("Listenning....");
        }
        else {
            emit send_to_mainwindow("Error while start.");
        }
        break;
    case PortValid::INCORRECT:
            emit send_to_mainwindow("Port number is incorrect.");
        break;
    }
}

void MultiThreadServer::get_request(const QString& msg)
{
    emit send_to_mainwindow_client_point(msg);
}
