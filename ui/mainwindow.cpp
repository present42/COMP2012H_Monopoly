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
    initGameWindow();

    //We assume this is remote server
    if(game_instance != nullptr) delete game_instance;
    game_instance = new Server;

    //Here, we connect the signal from server to the client (GUI)
    //1. signal that informs new player is created
    //connect(game_instance, &Server::init_player, game_window, &GameWindow::init_player);
    connect(game_instance, &Server::init_player, game_window, &GameWindow::init_player);
    connect(game_instance, &Server::current_player_set, game_window, &GameWindow::setCurrentPlayer);
    connect(game_instance, &Server::status_changed, game_window, &GameWindow::handleStatusChange);
    connect(game_instance, &Server::dice_thrown, game_window, &GameWindow::showDiceNumber);
    connect(game_instance, &Server::player_moved, game_window, &GameWindow::moveToken);
    connect(game_instance, &Server::pass_asset_price, game_window, &GameWindow::getAssetPrice);

    //connect(game_instance, &Server::current_player_set, game_window, &GameWindow::setCurrentPlayer);
    //Here we define signals from client GUI to server
    //1. when the client clicks the "roll the dice button"
    connect(game_window->getRollDiceWidget(), &RollDiceWidget::roll_button_clicked, game_instance, &Server::roll_dice);
    connect(game_window, &GameWindow::turn_finished, game_instance, &Server::next_player);
    connect(game_window->getUnpurchasedAssetWidget(), &UnpurchasedAssetWidget::purchase_button_clicked, game_instance, &Server::purchaseProperty);

    //If the game window is closed, open the main window
    connect(game_window, &GameWindow::closed, this, &MainWindow::game_window_closed_handler);

    /*
     * For the simplicity, we assume 4 players participate here.
     *
     */
    game_instance->add_player(new Player(0, Token::BOOT));
    game_instance->add_player(new Player(1, Token::CAR));
    //game_instance->add_player(new Player(2, Token::CAT));
    //game_instance->add_player(new Player(3, Token::SHIP));
    game_instance->start();

    this->hide();
    game_window->show();
}

void MainWindow::game_window_closed_handler() {
    this->show();
}

void MainWindow::initGameWindow() {
    if(game_window != nullptr) game_window = new GameWindow(nullptr);
}

void MainWindow::handler(int id) {
    qDebug() <<"HI";
    qDebug() << id;
}

