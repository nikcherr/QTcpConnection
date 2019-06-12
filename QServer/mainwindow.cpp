#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new MultiThreadServer(this);
    settings = new QSettings("someServerOrganization", "someServerApplication", this);
    serverPoint = new GeographicalPoint();
    clientPoint = new GeographicalPoint();

    QObject::connect(this, SIGNAL(send_to_server(const QString&)), server, SLOT(run(const QString&)));
    QObject::connect(server, SIGNAL(send_to_mainwindow(const QString&)), this, SLOT(get_from_server(const QString&)));
    QObject::connect(server, SIGNAL(send_to_mainwindow_client_point(const QString&)), this, SLOT(get_client_point(const QString&)));

    scene = new QGraphicsScene();
    pointServer = new Point(0, 0);
    pointClient = new Point();
    lineToClient = new Line();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(-250,-250,500,500);
    scene->addLine(-250,0,250,0,QPen(Qt::black));
    scene->addLine(0,-250,0,250,QPen(Qt::black));
    scene->addItem(pointServer);

    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    emit send_to_server(ui->lineEdit->text());
}

void MainWindow::get_from_server(const QString& msg)
{
    ui->textEdit->insertPlainText(msg + '\n');
}

void MainWindow::get_client_point(const QString& msg)
{
    int index = msg.indexOf(" ");
    float latitude = msg.left(index).toFloat();
    float longitude = msg.mid(index).toFloat();
    clientPoint->changeLatitude(latitude);
    clientPoint->changeLongitude(longitude);
    renderAzimuth();
}

void MainWindow::renderAzimuth()
{
    if(serverPoint->isSet() && clientPoint->isSet()){
        if(lineToClient != nullptr)
            scene->removeItem(lineToClient);
        float azimuth = serverPoint->calculateAzimuth(*clientPoint);
        //ui->textEdit->insertPlainText("Distance: " + QString::number(Distance(*serverPoint, *clientPoint)) + "\n");
        ui->textEdit->insertPlainText("Azimuth: " + QString::number(azimuth) + "\n");

        lineToClient->setAzimuth(azimuth);
        scene->addItem(lineToClient);
        scene->addItem(pointClient);
    }
}

void MainWindow::on_lat_degree_textChanged(const QString &arg1)
{
    serverPoint->changeLatitude({arg1.toInt(), ui->lat_minute->text().toInt(), ui->lat_second->text().toInt()});
    renderAzimuth();
}

void MainWindow::on_lat_minute_textChanged(const QString &arg1)
{
    serverPoint->changeLatitude({ui->lat_degree->text().toInt(), arg1.toInt(), ui->lat_second->text().toInt()});
    renderAzimuth();
}

void MainWindow::on_lat_second_textChanged(const QString &arg1)
{
    serverPoint->changeLatitude({ui->lat_degree->text().toInt(), ui->lat_minute->text().toInt(), arg1.toInt()});
    renderAzimuth();
}

void MainWindow::on_long_degree_textChanged(const QString &arg1)
{
    serverPoint->changeLongitude({arg1.toInt(), ui->long_minute->text().toInt(), ui->long_second->text().toInt()});
    renderAzimuth();
}

void MainWindow::on_long_minute_textChanged(const QString &arg1)
{
    serverPoint->changeLongitude({ui->long_degree->text().toInt(), arg1.toInt(), ui->long_second->text().toInt()});
    renderAzimuth();
}

void MainWindow::on_long_second_textChanged(const QString &arg1)
{
    serverPoint->changeLongitude({ui->long_degree->text().toInt(), ui->long_minute->text().toInt(), arg1.toInt(),});
    renderAzimuth();
}

void MainWindow::saveSettings()
{
    settings->setValue("portNumber", ui->lineEdit->text());
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
    ui->lineEdit->setText(settings->value("portNumber", "5555").toString());
    setGeometry(settings->value("geometry", QRect(200, 200, 400, 550)).toRect());
    settings->beginGroup("latitude");
    ui->lat_degree->setText(settings->value("degree", 30).toString());
    ui->lat_minute->setText(settings->value("minute", 20).toString());
    ui->lat_second->setText(settings->value("second", 12).toString());
    settings->endGroup();
    settings->beginGroup("longitude");
    ui->long_degree->setText(settings->value("degree", 15).toString());
    ui->long_minute->setText(settings->value("minute", 17).toString());
    ui->long_second->setText(settings->value("second", 20).toString());
    settings->endGroup();
}
