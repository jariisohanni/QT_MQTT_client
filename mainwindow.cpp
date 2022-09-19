#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonConnect, &QPushButton::released, this, &MainWindow::buttonConnectReleased);
}

void MainWindow::buttonConnectReleased()
{
  //Next we need to connect to the server
    QMessageBox::information(
        this,
        tr("Hi"),
        tr("Let's connect to server") );

}

MainWindow::~MainWindow()
{
    delete ui;
}

