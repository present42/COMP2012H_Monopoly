#include "ui/gamewindow.h"
#include "ui_gamewindow.h"

#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QPalette>

#include "blockuifactory.h"
#include "specialblockui.h"
#include "normalblockui.h"
#include "normalblockwithlabelui.h"
#include "src/player.h"

GameWindow::GameWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    dice(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/res/font/Dice.ttf")).at(0), 50))
{
    ui->setupUi(this);

    for(int i = 0; i < 40; i++) {
        block_ui[i] = BlockUIFactory::createBlock(this, i);
        block_ui[i]->render();
    }

    for(int i = 0; i < 4; i++) {
        tokens[i] = new TokenUI(this, TokenUI::Token::BOOT, &block_ui);
        tokens[i]->move(0);
    }

    initRollDiceWidget();
    this->show();
}

GameWindow::~GameWindow() {
    delete ui;
    if(roll_dice_widget) delete roll_dice_widget;
}

void GameWindow::initRollDiceWidget() {
    roll_dice_widget = new RollDiceWidget(this);
    roll_dice_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    roll_dice_widget->setPalette(pal);

    roll_dice_widget->show(); // should remove after making showRollDiceWidget()
}

void GameWindow::closeEvent(QCloseEvent *) {
    emit closed();
}

RollDiceWidget* GameWindow::getRollDiceWidget() {
    return roll_dice_widget;
}

void GameWindow::init_player(int id) {
    qDebug() << id << "from init_player()";
}

void GameWindow::statusChangeHandler(int status) {
    qDebug() << "statusChangeHandler" << status;
    switch (status) {
        case 1:
            roll_dice_widget->show();
            return;
        default:
            qDebug() << "this status is not defined yet..!";
            return;
    }
}

void GameWindow::hideAllDialogues(){
    roll_dice_widget->hide();
};
