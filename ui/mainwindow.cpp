#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

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
    if(this->game_instance) delete this->game_instance;
    this->game_instance = new Server;
    this->game_instance->startGUI();
    connect(this->game_instance->get_game_window(), &GameWindow::closed, this, &MainWindow::game_window_closed_handler);
    this->hide();
}

void MainWindow::game_window_closed_handler() {
    this->show();
}

