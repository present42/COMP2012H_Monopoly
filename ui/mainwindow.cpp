#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->startButton, &QPushButton::clicked, this, &MainWindow::startButton_clicked_handler);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButton_clicked_handler() {

}

