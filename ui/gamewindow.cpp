#include "ui/gamewindow.h"
#include "ui_gamewindow.h"

#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QPalette>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "blockuifactory.h"
#include "specialblockui.h"
#include "normalblockui.h"
#include "normalblockwithlabelui.h"
#include "src/player.h"

GameWindow::GameWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    game_status(-1),
    dice_font(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/res/font/Dice.ttf")).at(0), 50)),
    token_num(0)
{
    ui->setupUi(this);

    player_property_list_widget[0] = ui->tab1;
    player_property_list_widget[1] = ui->tab2;
    player_property_list_widget[2] = ui->tab3;
    player_property_list_widget[3] = ui->tab4;

    for(int i = 0; i < 4; ++i)
        ui->tabWidget->removeTab(0);

    for(int i = 0; i < 40; i++) {
        block_ui[i] = BlockUIFactory::createBlock(this, i);
        block_ui[i]->render();
    }

    token_list[0] = TokenUI::Token::BOOT;
    token_list[1] = TokenUI::Token::CAT;
    token_list[2] = TokenUI::Token::SHIP;
    token_list[3] = TokenUI::Token::CAR;

    initRollDiceWidget();
    initUnpurchasedAssetWidget();
    initEndTurnWidget();
    initOweMoneyWidget();
    initInJailWidget();

    initDice();

    this->show();
}

GameWindow::~GameWindow() {
    delete ui;
    if(roll_dice_widget) delete roll_dice_widget;
}

void GameWindow::initDice() {
    for(int i = 0; i < 2; ++i) {
        dice[i] = new QLabel(this);
        dice[i]->setGeometry(roll_dice_widget->x() + 20 + (i * 80),
                             roll_dice_widget->y() + 80,
                             80, 80);
        dice[i]->setText(QString::number(2));
        dice[i]->setFont(dice_font);
    }
}

void GameWindow::relocateDice() {
    for(int i = 0; i < 2; ++i) {
        dice[i]->setGeometry(roll_dice_widget->x() + 20 + (i * 80),
                             roll_dice_widget->y() + 80,
                             80, 80);
        dice[i]->setText(QString::number(0));
    }
}
/*
 * TODO - Move most of statements from init--Widget()
 *        to each class's constructor
 */
void GameWindow::initRollDiceWidget() {
    roll_dice_widget = new RollDiceWidget(this);
    roll_dice_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    roll_dice_widget->setPalette(pal);

    roll_dice_widget->hide();
}

void GameWindow::initUnpurchasedAssetWidget() {
    unpurchased_asset_widget = new UnpurchasedAssetWidget(this);
    unpurchased_asset_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    unpurchased_asset_widget->setPalette(pal);

    unpurchased_asset_widget->hide();
}

void GameWindow::initEndTurnWidget() {
    end_turn_widget = new EndTurnWidget(this);
    end_turn_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    end_turn_widget->setPalette(pal);

    connect(end_turn_widget->get_end_turn_button(), &QPushButton::clicked, this, &GameWindow::end_turn_button_clicked);
    end_turn_widget->hide();
}

void GameWindow::initOweMoneyWidget() {
    owe_money_widget = new OweMoneyWidget(this);
    owe_money_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    owe_money_widget->setPalette(pal);

    owe_money_widget->hide();
}

void GameWindow::initInJailWidget() {
    in_jail_widget = new InJailWidget(this);
    in_jail_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    in_jail_widget->setPalette(pal);

    in_jail_widget->hide();
}

void GameWindow::closeEvent(QCloseEvent *) {
    emit closed();
}

RollDiceWidget* GameWindow::getRollDiceWidget() {
    return roll_dice_widget;
}

void GameWindow::init_player(int id) {
    token_num++;
    tokens[id] = new TokenUI(this, token_list[id], &block_ui);

    initTabWidget(id);
    qDebug() << id << "from init_player()";
}

void GameWindow::initTabWidget(int new_tab) {
    ui->tabWidget->insertTab(new_tab, player_property_list_widget[new_tab], "Player " + QString::number(new_tab + 1) + QString(" ($1500)"));
}

void GameWindow::handleStatusChange(int status) {
    qDebug() << "statusChangeHandler with parameter" << status;
    switch (status) {
        case 1:
            relocateDice();
            roll_dice_widget->updatePlayer(current_token);
            roll_dice_widget->show();
            return;
        case 5:
            end_turn_widget->show();
            return;
        default:
            qDebug() << "this status is not defined yet..!";
            return;
    }
}

void GameWindow::showDiceNumber(int first, int second) {
    qDebug() << first << "&" << second;
    dice[0]->setText(QString::number(first));
    dice[1]->setText(QString::number(second));

    QParallelAnimationGroup *group = new QParallelAnimationGroup;

    for(int i = 0; i < 2; ++i) {
        QPropertyAnimation* anim = new QPropertyAnimation(dice[i], "geometry");
        anim->setDuration(1000);
        anim->setStartValue(dice[i]->geometry());
        anim->setEndValue(QRect(ui->tabWidget->x() + (i * 80), ui->tabWidget->y() + ui->tabWidget->height() + 40,
                                dice[i]->width(), dice[i]->height()));
        group->addAnimation(anim);
    }

    group->start();
}

void GameWindow::hideAllDialogues() {
    roll_dice_widget->hide();
}

void GameWindow::setCurrentPlayer(int index) {
    qDebug() << "setCurrentPlayer with" << index;
    current_token = index;
}

void GameWindow::moveToken(int position) {
    qDebug() << "moveToken" << position;
    tokens[current_token]->move(position);
}

void GameWindow::end_turn_button_clicked() {
    qDebug() << "end_turn_button_clicked";
    end_turn_widget->hide();
    emit turn_finished();
}
