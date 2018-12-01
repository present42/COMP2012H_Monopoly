#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game_instance(nullptr)
{
    ui->setupUi(this);
    connect(this->ui->startButton, &QPushButton::clicked, this, &MainWindow::startButton_clicked_handler);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButton_clicked_handler() {

    //We assume this is remote server
    if(game_instance != nullptr) delete game_instance;
    game_instance = new Server;

    connect(game_instance->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    game_instance->start();
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    this->show();
}
