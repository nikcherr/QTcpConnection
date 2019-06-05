#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include <QTcpSocket>
#include <QThread>
#include <QDateTime>

class SocketThread : public QThread
{
Q_OBJECT
public:
    explicit SocketThread(qintptr descriptor, QObject* parent = nullptr);
    ~SocketThread();
    void run();
signals:
    void get_client_point(const QString& msg);

public slots:
    void onReadyRead();
    void onDisconnect();
private:
    qintptr descriptor_;
    QTcpSocket* socket;
};

#endif // SOCKETTHREAD_H
