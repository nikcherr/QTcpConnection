#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <geographicalpoint.h>

enum class PortValid{
    CORRECT = 1,
    INCORRECT = 0
};

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    Client(QObject* parent = nullptr);
    PortValid setPortNumber(const std::string& port);
    ~Client();
    bool isConnected();

public slots:
    void readData();
    void set_address_port(const QString& address, const QString& port);
    void write_data_to_socket(const GeographicalPoint& data);

signals:
    void send_to_mainwindow(const QString& msg);
private:
    QTcpSocket* socket;
    int port;
};

#endif // CLIENT_H
