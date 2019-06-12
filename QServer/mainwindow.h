#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QGraphicsScene>
#include <multithreadserver.h>
#include <geographicalpoint.h>
#include <point.h>
#include <line.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveSettings();
    void loadSettings();
    void renderAzimuth();

signals:
    void send_to_server(const QString& port);

private slots:
    void on_pushButton_clicked();
    void get_from_server(const QString& msg);
    void get_client_point(const QString& msg);
    void on_lat_degree_textChanged(const QString &arg1);
    void on_lat_minute_textChanged(const QString &arg1);
    void on_lat_second_textChanged(const QString &arg1);
    void on_long_degree_textChanged(const QString &arg1);
    void on_long_minute_textChanged(const QString &arg1);
    void on_long_second_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSettings* settings;
    GeographicalPoint* serverPoint = nullptr;
    GeographicalPoint* clientPoint = nullptr;
    MultiThreadServer* server;
    QGraphicsScene* scene;
    Point* pointServer;
    Point* pointClient;
    Line* lineToClient = nullptr;
};

#endif // MAINWINDOW_H
