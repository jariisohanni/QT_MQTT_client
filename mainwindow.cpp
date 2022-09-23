#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mqttmessage.h"

#include <QMessageBox>
#include <QMqttClient>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connecting to user interface elements and their actions
    connect(ui->pushButtonConnect, &QPushButton::released, this, &MainWindow::buttonConnectReleased);
    connect(ui->pushButtonSubscribe, &QPushButton::released, this, &MainWindow::buttonSubsribeToTopic);
    connect(ui->pushButtonSend, &QPushButton::released, this, &MainWindow::buttonSendToTopic);

    //Clear the messages box
    ui->mqttMessages->clear();

    //Disable buttons at start
    ui->pushButtonSubscribe->setDisabled(true);
    ui->pushButtonSend->setDisabled(true);

    m_client = new QMqttClient(this);

    //Connecting MainWindow functions to MqttClients signal
    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MainWindow::mqttMessageReceived);
}

MainWindow::~MainWindow()
{
    delete m_client;
    delete ui;
}

void MainWindow::buttonConnectReleased()
{
   ui->pushButtonConnect->setDisabled(true);

    //Next we need to connect to the server
    m_client->setHostname(ui->lineEditUrl->text());
    m_client->setPort(1883); //Standard MQTT port

    ui->mqttMessages->append("Connecting to host...");

    //connect(m_client, &QMqttClient::messageReceived, this, &MainWindow::brokerDisconnected);

    m_client->connectToHost();

   /* connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
           const QString content = QDateTime::currentDateTime().toString()
                       + QLatin1String(" Received Topic: ")
                       + topic.name()
                       + QLatin1String(" Message: ")
                       + message
                       + QLatin1Char('\n');

           ui->mqttMessages->append(content);
    });*/

}

void MainWindow::brokerDisconnected()
{
    ui->pushButtonSend->setDisabled(true);
    ui->pushButtonSubscribe->setDisabled(true);
    ui->pushButtonConnect->setDisabled(false);
}

//This called everytime MQTT client changes state
//Possible states are { Disconnected, Connecting, Connected }
void MainWindow::updateStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change: ")
                    + QString::number(m_client->state());
                   // + QLatin1Char('\n');

    ui->mqttMessages->append(content);

    if(m_client->state() == QMqttClient::Connected)
    {

        //Yes we have connect
        ui->pushButtonSubscribe->setDisabled(false);
        ui->pushButtonConnect->setDisabled(true);
    }
    else if(m_client->state() == QMqttClient::Disconnected)
    {
        brokerDisconnected();
    }
}

void MainWindow::buttonSubsribeToTopic()
{

    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    if (!subscription)
    {
       QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
    }
    else
    {
        ui->mqttMessages->append("Subscribed to topic");
        ui->pushButtonSubscribe->setDisabled(true);
        ui->pushButtonSend->setDisabled(false);
    }
}

void MainWindow::buttonSendToTopic()
{
    if (m_client->publish(ui->lineEditTopic->text(), ui->lineEditMessage->text().toUtf8()) == -1)
    {
       QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
    }
    else
    {
        ui->mqttMessages->append("Posted message to topic");
    }
}


void MainWindow::mqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
   const QString content = QDateTime::currentDateTime().toString()
               + QLatin1String(" Received Topic: ")
               + topic.name()
               + QLatin1String(" Message: ")
               + message
               + QLatin1Char('\n');

   ui->mqttMessages->append(content);
}




//THESE HERE ONLY MOCKUPS

void MainWindow::messagesReceivedMockup()
{
    MqttMessage msg;
    msg.setMessage("Hi from MQTT");
    msg.setSender("Device 1");

    QString temp = QString::fromStdString(msg.print());
    ui->mqttMessages->append(temp);
}









