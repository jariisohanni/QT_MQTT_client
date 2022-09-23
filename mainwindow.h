#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QMqttClient;
class QMqttTopicName;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectoToURL(QString url) const;

private:
    void messagesReceivedMockup();

private slots:
      //UI slots
      void buttonConnectReleased();
      void buttonSubsribeToTopic();
      void buttonSendToTopic();

      //MQTT Related stuff here
      void updateStateChange();
      void brokerDisconnected();
      void mqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    Ui::MainWindow *ui;
    QMqttClient* m_client;
};
#endif // MAINWINDOW_H
