#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient = new Client();
    clientPoint = new GeographicalPoint();

    QObject::connect(tcpClient, SIGNAL(send_to_mainwindow(const QString&)), this, SLOT(get_message_from_client(const QString&)));
    QObject::connect(this, SIGNAL(send_address_port(const QString&, const QString&)), tcpClient, SLOT(set_address_port(const QString&, const QString&)));
    QObject::connect(this, SIGNAL(send_data_to_socket(const GeographicalPoint&)), tcpClient, SLOT(write_data_to_socket(const GeographicalPoint&)));

    settings = new QSettings("someClientOrganization", "someClientApplication", this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit send_address_port(ui->addressEdit->text(), ui->portEdit->text());
    emit send_data_to_socket(*clientPoint);
}

void MainWindow::get_message_from_client(const QString &msg)
{
    ui->textEdit->insertPlainText(msg + '\n');
}

void MainWindow::saveSettings()
{
    settings->setValue("portNumber", ui->portEdit->text());
    settings->setValue("address", ui->addressEdit->text());
    settings->setValue("geometry", geometry());
    settings->beginGroup("latitude");
    settings->setValue("degree", ui->lat_degree->text());
    settings->setValue("minute", ui->lat_minute->text());
    settings->setValue("second", ui->lat_second->text());
    settings->endGroup();
    settings->beginGroup("longitude");
    settings->setValue("degree", ui->long_degree->text());
    settings->setValue("minute", ui->long_minute->text());
    settings->setValue("second", ui->long_second->text());
    settings->endGroup();
}

void MainWindow::loadSettings()
{
    ui->portEdit->setText(settings->value("portNumber", "5555").toString());
    ui->addressEdit->setText(settings->value("address", "127.0.0.1").toString());
    setGeometry(settings->value("geometry", QRect(100, 100, 360, 260)).toRect());
    settings->beginGroup("latitude");
    ui->lat_degree->setText(settings->value("degree", -30).toString());
    ui->lat_minute->setText(settings->value("minute", 45).toString());
    ui->lat_second->setText(settings->value("second", 0).toString());
    settings->endGroup();
    settings->beginGroup("longitude");
    ui->long_degree->setText(settings->value("degree", -15).toString());
    ui->long_minute->setText(settings->value("minute", 0).toString());
    ui->long_second->setText(settings->value("second", 0).toString());
    settings->endGroup();
}

void MainWindow::on_lat_degree_textChanged(const QString &arg1)
{
    clientPoint->changeLatitude({arg1.toInt(), ui->lat_minute->text().toInt(), ui->lat_second->text().toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}

void MainWindow::on_lat_minute_textChanged(const QString &arg1)
{
    clientPoint->changeLatitude({ui->lat_degree->text().toInt(), arg1.toInt(), ui->lat_second->text().toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}

void MainWindow::on_lat_second_textChanged(const QString &arg1)
{
    clientPoint->changeLatitude({ui->lat_degree->text().toInt(), ui->lat_minute->text().toInt(), arg1.toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}

void MainWindow::on_long_degree_textChanged(const QString &arg1)
{
    clientPoint->changeLongitude({arg1.toInt(), ui->long_minute->text().toInt(), ui->long_second->text().toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}

void MainWindow::on_long_minute_textChanged(const QString &arg1)
{
    clientPoint->changeLongitude({ui->long_degree->text().toInt(), arg1.toInt(), ui->long_second->text().toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}

void MainWindow::on_long_second_textChanged(const QString &arg1)
{
    clientPoint->changeLongitude({ui->long_degree->text().toInt(), ui->long_minute->text().toInt(), arg1.toInt()});
    if(tcpClient->isConnected())
        emit send_data_to_socket(*clientPoint);
}
