#ifndef MULTITHREADSERVER_H
#define MULTITHREADSERVER_H
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>

enum class PortValid{
    CORRECT = 1,
    INCORRECT = 0
};

class MultiThreadServer : public QTcpServer
{
    Q_OBJECT

public:
    MultiThreadServer(QObject* parent = nullptr);
    PortValid setPortNumber(const std::string& port);
    void incomingConnection(qintptr handle);
private:
    int port;

signals:
    void send_to_mainwindow(const QString& msg);
    void send_to_mainwindow_client_point(const QString& msg);
public slots:
    void run(const QString& port);
    void get_request(const QString& msg);
};

#endif // MULTITHREADSERVER_H
