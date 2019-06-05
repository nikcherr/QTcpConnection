#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QGraphicsScene>
#include <multithreadserver.h>
#include <geographicalpoint.h>
#include <point.h>

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

signals:
    void send_to_server(const QString& port);

private slots:
    void on_pushButton_clicked();
    void get_from_server(const QString& msg);
    void get_client_point(const QString& msg);

private:
    Ui::MainWindow *ui;
    QSettings* settings;
    GeographicalPoint* serverPoint;
    GeographicalPoint* clientPoint;
    MultiThreadServer* server;
    QGraphicsScene* scene;
    Point* pointServer;
};

#endif // MAINWINDOW_H
