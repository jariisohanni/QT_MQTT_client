#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class QTextEdit;

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
    void httpReplyFinished(QNetworkReply *reply);

    QNetworkAccessManager *manager;

private:
    void messagesReceivedMockup();

private slots:
      void buttonConnectReleased();
      void buttonSubsribeToTopic();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
