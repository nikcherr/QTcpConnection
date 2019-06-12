#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <client.h>
#include <geographicalpoint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void saveSettings();
    void loadSettings();

private slots:
    void on_pushButton_clicked();
    void get_message_from_client(const QString& msg);
    void on_lat_degree_textChanged(const QString &arg1);
    void on_lat_minute_textChanged(const QString &arg1);
    void on_lat_second_textChanged(const QString &arg1);
    void on_long_degree_textChanged(const QString &arg1);
    void on_long_minute_textChanged(const QString &arg1);
    void on_long_second_textChanged(const QString &arg1);

signals:
    void send_address_port(const QString& address, const QString& port);
    void send_data_to_socket(const GeographicalPoint& data);

private:
    Ui::MainWindow *ui;
    Client* tcpClient;
    GeographicalPoint* clientPoint;
    QSettings* settings;
};

#endif // MAINWINDOW_H
