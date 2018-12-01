#include "ui/gamewindow.h"
#include "ui_gamewindow.h"

#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QPalette>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTabBar>

#include "blockuifactory.h"
#include "specialblockui.h"
#include "normalblockui.h"
#include "normalblockwithlabelui.h"
#include "src/block.h"
#include "src/property.h"
#include "src/railroad.h"
#include "src/utility.h"


GameWindow::GameWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    game_status(-1),
    dice_font(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/res/font/Dice.ttf")).at(0), 50)),
    token_num(0),
    current_token(0)
{
    ui->setupUi(this);   
    for(int i = 0; i < 4; ++i) money[i] = 1500;

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
    initPayRentWidget();
    initCardWidget();
    initSimpleWidget();

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

    in_jail_widget->show();
}

void GameWindow::initPayRentWidget() {
    pay_rent_widget = new PayRentWidget(this);
    pay_rent_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    pay_rent_widget->setPalette(pal);

    pay_rent_widget->hide();
}

void GameWindow::initCardWidget() {
    card_widget = new CardWidget(this);
    card_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    card_widget->setPalette(pal);

    card_widget->hide();
}

void GameWindow::initSimpleWidget() {
    simple_widget = new SimpleWidget(this);
    simple_widget->setAutoFillBackground(true);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    simple_widget->setPalette(pal);

    simple_widget->hide();
}

void GameWindow::closeEvent(QCloseEvent *) {
    emit closed();
}

RollDiceWidget* GameWindow::getRollDiceWidget() {
    return roll_dice_widget;
}

UnpurchasedAssetWidget* GameWindow::getUnpurchasedAssetWidget() {
    return unpurchased_asset_widget;
}

PayRentWidget* GameWindow::getPayRentWidget() {
    return pay_rent_widget;
}

CardWidget* GameWindow::getCardWidget() {
    return card_widget;
}

SimpleWidget* GameWindow::getSimpleWidget() {
    return simple_widget;
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
        case 2:
            unpurchased_asset_widget->setPreview(tokens[current_token]->getPosition());
            unpurchased_asset_widget->show();
            return;
        case 3:
            pay_rent_widget->setPayer(tokens[current_token]);
            pay_rent_widget->show();
            return;
        case 5:
            card_widget->show();
            return;
        case 6:
            simple_widget->setExplanation("Nothing to do..");
            simple_widget->show();
            return;
        case 10:
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

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameWindow::getAssetPrice(int price) {
    unpurchased_asset_widget->setPrice(price);
}

void GameWindow::getRentInfo(int receiver, int amount) {
    pay_rent_widget->setRent(amount);
    pay_rent_widget->setReceiver(tokens[receiver]);
}

void GameWindow::hideAllDialogues() {
    roll_dice_widget->hide();
}

void GameWindow::setCurrentPlayer(int index) {
    qDebug() << "setCurrentPlayer with" << index;
    ui->tabWidget->setCurrentIndex(index);
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

void GameWindow::setCardInstruction(bool isChanceCard, QString instruction) {
    card_widget->setReader(current_token);
    if(isChanceCard) {
        card_widget->setInstruction("CHANCE CARD\n\n" + instruction);
    } else {
        card_widget->setInstruction("COMMUNITY CHEST CARD\n\n" + instruction);
    }
}

void GameWindow::buyAsset(int position) {
    QString find_name = QString("\\b(\\w*") + "a" + QString::number(position) + "_" + "\\w*)\\b";
    QRegExp regex (find_name);
    QList<QLabel *> list = ui->tabWidget->findChildren<QLabel*>(regex);

    QList<QLabel *>::Iterator temp;
    for(temp = list.begin(); temp != list.end(); temp++) {
        qDebug() << (*temp)->parent()->objectName();
        if((*temp)->parent()->objectName() == (QString("tab") + QString::number(current_token + 1))) {
            (*temp)->setStyleSheet((*temp)->styleSheet().append(";background-color: white;"));
        } else {
            (*temp)->setStyleSheet((*temp)->styleSheet().append(";background-color: grey;"));
        }
    }
}

void GameWindow::payToBank(int amount) {
    updateMoney(current_token, money[current_token] - amount);
}

void GameWindow::payToOtherPlayer(int receiver, int amount) {
    updateMoney(current_token, money[current_token] - amount);
    updateMoney(receiver, money[receiver] + amount);
}

void GameWindow::payToOthers(int amount) {
    for(int i = 0; i < token_num; ++i) {
        if(i == current_token) {
            updateMoney(current_token, money[current_token] - amount * (token_num - 1));
        } else {
            updateMoney(i, money[i] + amount);
        }
    }
}

void GameWindow::receiveFromBank(int amount) {
    updateMoney(current_token, money[current_token] + amount);
}

void GameWindow::receiveFromOthers(int amount) {
    for(int i = 0; i < token_num; ++i) {
        if(i == current_token) {
            updateMoney(current_token, money[current_token] + amount * (token_num - 1));
        } else {
            updateMoney(i, money[i] - amount);
        }
    }
}

void GameWindow::updateMoney(int player, int amount) {
    ui->tabWidget->setTabText(player, "Player " + QString::number(player + 1) + " ($" + QString::number(amount) + ")");
}

void GameWindow::refresh(vector<Player*> players, Block* block[40]) {
    QLCDNumber *home[4] = { ui->home_number, ui->home_number_2, ui->home_number_3, ui->home_number_4};
    QLCDNumber *hotel[4] = { ui->hotel_number_1, ui->hotel_number_2, ui->hotel_number_3, ui->hotel_number_4};

    for(vector<Player*>::iterator temp = players.begin(); temp != players.end(); temp++) {
        updateMoney((*temp)->get_playerid(), (*temp)->get_money());
        tokens[(*temp)->get_playerid()]->move((*temp)->get_playerposition());
        home[(*temp)->get_playerid()]->display(10);
        home[(*temp)->get_playerid()]->show();

        hotel[(*temp)->get_playerid()]->display(10);
        hotel[(*temp)->get_playerid()]->show();
    }
    int j =0;
    for (vector<Player*>::iterator temp = players.begin(); temp != players.end(); temp++){
        for(int i =0 ; i < 40;i++){
            Asset* asset = dynamic_cast<Asset*>(block[i]);
            if(asset != nullptr){
                if(asset->get_owner() == nullptr){
                    update(j,i,-3);
                }else if (asset->get_owner() != *temp){
                    update(j,i,-2);
                }else if (asset->get_owner() == *temp&&
                          asset->get_mortgage_status()){
                    update(j,i,-1);
                }else{
                    Property* property = dynamic_cast<Property*>(block[i]);
                    if (property == nullptr){
                        update(j,i,0);
                    }else if (property->get_hotel() == 0){
                        update(j,i,property->get_house());
                    }else{
                        update(j,i,5);
                    }
                }
            }
        }
        j++;
    }

}
