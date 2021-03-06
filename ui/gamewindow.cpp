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


GameWindow::GameWindow(QWidget* parent, Block* board[40]) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    board(board),
    game_status(-1),
    dice_font(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/res/font/Dice.ttf")).at(0), 50)),
    token_num(0),
    current_token(0)
{
    ui->setupUi(this);

    ui->warning;

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
        connect(block_ui[i], &AbstractBlockUI::clicked, this, &GameWindow::handleButtonClicked);
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
    hideWarningMessage();
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

InJailWidget* GameWindow::getInJailWidget() {
    return in_jail_widget;
}

OweMoneyWidget* GameWindow::getOweMoneyWidget() {
    return owe_money_widget;
}

QPushButton* GameWindow::getBuildButton() {
    return ui->buildButton;
}

QPushButton* GameWindow::getMortgageButton() {
    return ui->mortageButton;
}

QPushButton* GameWindow::getUnmortgageButton() {
    return ui->unmortgageButton;
}

QPushButton* GameWindow::getSellButton() {
    return ui->sellButton;
}


void GameWindow::init_player(int id) {
    QLabel* list[] = { ui->token_1, ui->token_2, ui->token_3, ui->token_4 };

    token_num++;
    tokens[id] = new TokenUI(this, token_list[id], &block_ui);
    initTabWidget(id);

    list[id]->setPixmap(tokens[id]->pixmap()->scaled(list[id]->width(), list[id]->height(), Qt::KeepAspectRatio));

    qDebug() << id << "from init_player()";
}

void GameWindow::initTabWidget(int new_tab) {
    ui->tabWidget->insertTab(new_tab, player_property_list_widget[new_tab], "Player " + QString::number(new_tab + 1) + QString(" ($1500)"));
}

void GameWindow::handleStatusChange(int status) {
    qDebug() << "statusChangeHandler with parameter" << status;
    int amount, pos;
    Asset* temp;

    pos = tokens[current_token]->getPosition();
    temp = dynamic_cast<Asset*>(board[pos]);

    owe_money_widget->hide();
    switch (status) {
        case 0:
            in_jail_widget->show();
            return;
        case 1:
            relocateDice();
            roll_dice_widget->updatePlayer(current_token);
            roll_dice_widget->show();
            return;
        case 2:
            unpurchased_asset_widget->setPreview(tokens[current_token]->getPosition());
            if(temp != nullptr) unpurchased_asset_widget->setPrice(temp->get_cost_value());
            unpurchased_asset_widget->show();
            return;
        case 3:
            pay_rent_widget->setPayer(tokens[current_token]);

            if(temp != nullptr) {
                pay_rent_widget->setRent(temp->get_rent());
                pay_rent_widget->setReceiver(tokens[temp->get_owner()->get_playerid()]);
            }
            pay_rent_widget->show();
            return;
        case 4:
            amount = tokens[current_token]->getPosition() == 38 ? 100 : 200;
            simple_widget->setExplanation("You have to pay $" + QString::number(amount) + " to the bank.");
            simple_widget->show();
            return;
        case 5:
            card_widget->show();
            return;
        case 6:
            simple_widget->setType(6);
            simple_widget->setExplanation("Nothing to do..");
            simple_widget->show();
            return;
        case 10:
            end_turn_widget->setPlayerID(current_token);
            end_turn_widget->show();
            return;
        case 11:
            simple_widget->setType(11);
            simple_widget->setExplanation("Click the place in which you want to build");
            simple_widget->show();
            return;
        case 12:
            simple_widget->setType(12);
            simple_widget->setExplanation("Click the place in which you want to mortgage.\nYou cannot mortgage the property in which buildings are built");
            simple_widget->show();
            return;
        case 13:
            simple_widget->setType(13);
            simple_widget->setExplanation("Click the place in which you want to unmortgage.");
            simple_widget->show();
            return;
        case 14:
            simple_widget->setType(14);
            simple_widget->setExplanation("Click the place in which you want to sell.");
            simple_widget->show();
            return;
        case 20:
            owe_money_widget->show();
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
    qDebug() << "setCurrentPlayer" << index;
    QLabel* list[] = { ui->token_1, ui->token_2, ui->token_3, ui->token_4 };
    for(int i = 0; i < 4; ++i) {
        if(i == index) {
            list[i]->setStyleSheet("border: 2px solid red; qproperty-alignment: AlignCenter;");
        } else {
            list[i]->setStyleSheet("border: 2px solid black; qproperty-alignment: AlignCenter;");
        }
    }
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

void GameWindow::setCardInstruction(bool isCommunityChest, QString instruction) {
    card_widget->setReader(current_token);
    if(isCommunityChest) {
        card_widget->setInstruction("COMMUNITY CHEST CARD\n\n" + instruction);
    } else {
        card_widget->setInstruction("CHANCE CARD\n\n" + instruction);
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

void GameWindow::updateMoney(int player, int amount, bool bankrupt) {
    QLabel* list[] = { ui->token_1, ui->token_2, ui->token_3, ui->token_4 };

    if(!bankrupt) ui->tabWidget->setTabText(player, "Player " + QString::number(player + 1) + " ($" + QString::number(amount) + ")");
    else {
        ui->tabWidget->setTabText(player, "Bankrupt");
        list[player]->setText("BANKRUPT");
    }
}

QString GameWindow::getBorderStyle(int position) {
    switch(position) {
        case 1: case 3:
            return "border: 1.5px solid #955436;";
        case 5: case 15: case 25: case 35:
            return "border: 1.5px solid #ccc;";
        case 6: case 8: case 9:
            return "border: 1.5px solid #ade1fa;";
        case 11: case 13: case 14:
            return "border: 1.5px solid #d94999;";
        case 16: case 18: case 19:
            return "border: 1.5px solid #f89734;";
        case 21: case 23: case 24:
            return "border: 1.5px solid #ee3338;";
        case 26: case 27: case 29:
            return "border: 1.5px solid #fff213;";
        case 31: case 32: case 34:
            return "border: 1.5px solid #00a85a;";
        case 37: case 39:
            return "border: 1.5px solid #0077be;";
        case 12: case 28:
            return "border: 1.5px solid #ffffff;";

    }
}

void GameWindow::updateAssetInfo(int player, int position, int value) {
    QString find_name = QString("\\b(\\w*") + "a" + QString::number(position) + "_" + QString::number(player+1) + "\\w*)\\b";
    QRegExp regex (find_name);
    QList<QLabel *> list = ui->tabWidget->findChildren<QLabel*>(regex);

    if(list.size() == 0) return;

    QLabel* block = *(list.begin());
    if(block == nullptr) {
        qDebug() << "something goes wrong.";
        return;
    }

    if(value >= -1) {
        block->setStyleSheet(getBorderStyle(position) + "background-color: white");
        block->setText("");
        block->setAlignment(Qt::AlignCenter);
        switch(value) {
            case 5:
                block->setText("HOTEL");
                break;
            case 4:
            case 3:
            case 2:
            case 1:
                block->setText("HOUSE\n" + QString::number(value));
                break;
            case 0:
                break;
            case -1:
                block->setText("MORT\nGAGED");
                break;
            default:
                block->setText("ERROR");
        }
    } else if(value == -2) {
        block->setStyleSheet(getBorderStyle(position) + "background-color: grey");
    } else {
        block->setStyleSheet(getBorderStyle(position) + "background-color: transparent");
    }
}

void GameWindow::refresh(vector<Player*> players, Block* (*block)[40]) {
    QLCDNumber *home[4] = { ui->home_number, ui->home_number_2, ui->home_number_3, ui->home_number_4};
    QLCDNumber *hotel[4] = { ui->hotel_number_1, ui->hotel_number_2, ui->hotel_number_3, ui->hotel_number_4};
    QLCDNumber *jailcard[4] = { ui->jailcard_number_1, ui->jailcard_number_2, ui->jailcard_number_3, ui->jailcard_number_4 };

    for(vector<Player*>::iterator temp = players.begin(); temp != players.end(); temp++) {
        updateMoney((*temp)->get_playerid(), (*temp)->get_money(), (*temp)->islosed());
        tokens[(*temp)->get_playerid()]->move((*temp)->get_playerposition());
        home[(*temp)->get_playerid()]->display((*temp)->get_totalhouse());
        home[(*temp)->get_playerid()]->show();

        hotel[(*temp)->get_playerid()]->display((*temp)->get_totalhotel());
        hotel[(*temp)->get_playerid()]->show();

        int id, num;
        (*temp)->have_jailcard(id);

        if(id == 0 || id == 1) num = 1;
        else if(id == 2) num = 2;
        else num = 0;

        jailcard[(*temp)->get_playerid()]->display(num);
        hotel[(*temp)->get_playerid()]->show();
    }

    int j =0;
    for (vector<Player*>::iterator temp = players.begin(); temp != players.end(); temp++){
        for(int i =0 ; i < 40; i++){
            Asset* asset = dynamic_cast<Asset*>((*block)[i]);
            if(asset != nullptr){
                if(asset->get_owner() == nullptr){
                    updateAssetInfo(j, i, -3);
                } else if (asset->get_owner() != *temp){
                    updateAssetInfo(j, i, -2);
                } else if (asset->get_owner() == *temp&&
                          asset->get_mortgage_status()){
                    updateAssetInfo(j, i, -1);
                } else{
                    Property* property = dynamic_cast<Property*>((*block)[i]);
                    if (property == nullptr){
                        updateAssetInfo(j,i,0);
                    } else if (property->get_hotel() == 0){
                        updateAssetInfo(j, i, property->get_house());
                    } else{
                        updateAssetInfo(j, i, 5);
                    }
                }
            }
        }
        j++;
    }

}

void GameWindow::handleButtonClicked(int position) {
    emit block_clicked(position);
}

void GameWindow::updateInJailDialogue(bool affordable, bool have_card) {
    if(affordable) in_jail_widget->getPayButton()->show();
    else in_jail_widget->getPayButton()->hide();

    if(have_card) in_jail_widget->getUseCardButton()->show();
    else in_jail_widget->getUseCardButton()->hide();
}

void GameWindow::setWarningMesseage(QString message) {
    ui->warning->setText(message);
}

void GameWindow::hideWarningMessage() {
    ui->warning->setText("");
}

void GameWindow::hideToken(int id) {
    tokens[id]->hide();
}
