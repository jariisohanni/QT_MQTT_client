#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mqttmessage.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonConnect, &QPushButton::released, this, &MainWindow::buttonConnectReleased);
    connect(ui->pushButtonSubscribe, &QPushButton::released, this, &MainWindow::buttonSubsribeToTopic);

    ui->mqttMessages->clear();

    messagesReceivedMockup();

    ui->pushButtonSubscribe->setDisabled(true);


    manager = new QNetworkAccessManager(this);
    connectoToURL("http://www.google.com");

}



void MainWindow::connectoToURL(QString url) const {
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::httpReplyFinished);
    manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::httpReplyFinished(QNetworkReply *reply)
{
    QString answer = reply->readAll();
     ui->mqttMessages->append(answer);
}

void MainWindow::messagesReceivedMockup()
{
    MqttMessage msg;
    msg.setMessage("Hi from MQTT");
    msg.setSender("Device 1");

    QString temp = QString::fromStdString(msg.print());
    ui->mqttMessages->append(temp);
}

void MainWindow::buttonConnectReleased()
{
   ui->pushButtonConnect->setDisabled(true);
  //Next we need to connect to the server
    QMessageBox::information(
        this,
        tr("Hi"),
        tr("Let's connect to server") );

  ui->pushButtonConnect->setDisabled(false);

}

void MainWindow::buttonSubsribeToTopic()
{

}

MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}

