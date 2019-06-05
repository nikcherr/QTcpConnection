#include "client.h"

Client::Client(QObject *parent)
{

}

PortValid Client::setPortNumber(const std::__cxx11::string &port)
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

Client::~Client()
{
    socket->close();
}

void Client::readData()
{
    QByteArray data = socket->readAll();
}

void Client::set_address_port(const QString &address, const QString &port)
{
    switch(setPortNumber(port.toStdString())){
    case PortValid::CORRECT:
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

        socket->connectToHost(address, this->port);
        if(socket->waitForConnected(2000)){
            emit send_to_mainwindow("Connect to server.");
        }
        else{
            emit send_to_mainwindow("Connection timeout.");
        }
        break;
    case PortValid::INCORRECT:
        emit send_to_mainwindow("Port number is incorrect.");
        break;
    }
}

void Client::write_data_to_socket(const GeographicalPoint& data)
{
    QString out = QString::number(data.getLatitude()) + " " + QString::number(data.getLongitude());
    socket->write(out.toUtf8());
}
