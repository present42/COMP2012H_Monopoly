#include "server.h"
#include "token.h"

#include <cstdlib>
#include <ctime>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QString>
#include <QFile>
#include <deque>

using namespace std;

Server::Server():
  current_player(nullptr),
  double_count(0)
{
    srand(time(0));

    if(gamewindow != nullptr) gamewindow = new GameWindow(nullptr,block);

    add_player(new Player(0, Token::BOOT));
    add_player(new Player(1, Token::CAR));
    add_player(new Player(2, Token::CAT));
    add_player(new Player(3, Token::SHIP));

    connect(gamewindow->getRollDiceWidget(), &RollDiceWidget::roll_button_clicked, this, &Server::roll_dice);
    connect(gamewindow, &GameWindow::turn_finished, this, &Server::next_player);
    connect(gamewindow->getUnpurchasedAssetWidget(), &UnpurchasedAssetWidget::purchase_button_clicked, this, &Server::purchaseProperty);
    connect(gamewindow->getSimpleWidget(), &SimpleWidget::ok_button_clicked, this, &Server::handleSimpleWidgetOKButton);
    connect(gamewindow->getPayRentWidget(), &PayRentWidget::ok_button_clicked, this, &Server::checkdouble);
    connect(gamewindow->getCardWidget(), &CardWidget::ok_button_clicked, this, &Server::drawn_after);

    connect(gamewindow->getBuildButton(), &QPushButton::clicked, this, &Server::buildSomething);
    connect(gamewindow->getMortgageButton(), &QPushButton::clicked, this, &Server::mortgageSomething);
    connect(gamewindow->getUnmortgageButton(), &QPushButton::clicked, this, &Server::unmortgageSomething);
    connect(gamewindow->getSellButton(), &QPushButton::clicked, this, &Server::sellSomething);

    connect(gamewindow->getInJailWidget(), &InJailWidget::injail_choose, this, &Server::in_jail_action);
    connect(gamewindow, &GameWindow::block_clicked, this, &Server::block_clicked_handler);
    connect(gamewindow->getOweMoneyWidget(), &OweMoneyWidget::declare_bankrupt_button_clicked, this, &Server::handleBankruptcy);
    gamewindow->show();
}

Server::~Server() {
    for(vector<Player*>::iterator p = players.begin();
        p!= players.end() ; ++p)
    {
        delete *p ;
    }

    for(int i =0 ;i < 40 ; ++i){
        if( i ==17 || i == 33 || i ==7 || i ==12 || i ==36)
            continue;
        delete block[i];
    }
}

void Server::initboard(){
    // init the property first

    QFile file;
    file.setFileName(":/res/json/property.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);


    QJsonParseError jsonError;
    QJsonDocument Json = QJsonDocument::fromJson(file.readAll(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        qDebug() << jsonError.errorString();
    }

    QList<QVariant> list = Json.toVariant().toList();
    for(QList<QVariant>::iterator p = list.begin();p != list.end(); ++p){
        QJsonObject obj = p->toJsonObject();
        int pos = obj["position"].toInt();
        int cost = obj["cost"].toInt();
        int housecost = obj["housecost"].toInt();
        QJsonArray array = obj["rentlist"].toArray();
        vector<int> rentlist ;
        for(QJsonArray::iterator i =array.begin() ; i != array.end() ; i++){
            rentlist.push_back(i->toInt());
        }
        QString title = obj["title"].toString();
        Property::Group group = (Property::Group)obj["Group"].toInt();
        block[pos] = new Property(&block,nullptr,title,cost,housecost,rentlist,group);
    }
    file.close();

    //init of railroad silly no json ar
    block[5] = new Railroad(&block,nullptr,"Reading Railroad",200);
    block[15] = new Railroad(&block,nullptr,"Pennsylvania Railroad",200);
    block[25] = new Railroad(&block,nullptr,"B. & O. Railroad",200);
    block[35] = new Railroad(&block,nullptr,"Short Line",200);

    //init of utilty
    block[12] = new Utility(&block,nullptr,"Electric Company",150);
    block[28] = new Utility(&block,nullptr,"Water Works",150);

    //nothing block
    block[0] = new Block(&block);
    block[10] = new Block(&block);
    block[20] = new Block(&block);

    //init gotojail
    block[30] = new GotoJail(&block);

    //init charge
    block[4] = new Charge(&block,200);
    block[38] = new Charge(&block,100);

    //init card
    vector<Card *> Chance;
    vector<Card *> Community_chest;

    //init chance
    file.setFileName(":/res/json/chance_card.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    Json = QJsonDocument::fromJson(file.readAll(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        qDebug() << jsonError.errorString();
    }

    list = Json.toVariant().toList();
    for(QList<QVariant>::iterator p = list.begin();p != list.end(); ++p){
        QJsonObject obj = p->toJsonObject();
        int id = obj["id"].toInt();
        QString type = obj["type"].toString();
        QString explanation = obj["explanation"].toString();
//        qDebug() << type << explanation;
        Chance.push_back(new Card(id,explanation,type));


    }

    file.close();

    //init community_chest
    file.setFileName(":/res/json/community_chest_card.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    Json = QJsonDocument::fromJson(file.readAll(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        //qDebug() << jsonError.errorString();
    }

    list = Json.toVariant().toList();
    for(QList<QVariant>::iterator p = list.begin();p != list.end(); ++p){
        QJsonObject obj = p->toJsonObject();
        int id = obj["id"].toInt();
        QString type = obj["type"].toString();
        QString explanation = obj["explanation"].toString();

        Community_chest.push_back(new Card(id,explanation,type));

    }
    file.close();
    qDebug()<< "Chance size" << Chance.size();
    chance_block = new SelectCard(&block, 0, players, Chance);
    community_block = new SelectCard(&block, 1,  players , Community_chest);

    //2, 17, 33 cc
    block[2] = block [17] = block [33] = community_block;
    //7, 22, 36 c
    block[7] = block [22] = block [36] = chance_block;


}

GameWindow* Server::get_game_window() {
    return gamewindow;
}

void Server::add_player(Player* new_player) {
    if(players.size() < 4) {
        new_player->set_money(0);
        players.push_back( new_player);
        gamewindow->init_player(new_player->get_playerid());
    } else return;
}

/*
 * [Game Flow & Status]
 * 0 : jail
 * 1 : Before rolling the dice
 *
 * 2 : Buy or Auction event
 * 3 : Pay rent event (Player A -> Player B) B rent
 * 5 : card
 *
 * 10 : Before ending his turn
 *
 * 11 : build
 * 12 : mortgage
 * 13 : unmortage
 * 14 : sell
 *
 * 20 : Sell your property or go bankrupt
 *
 */
void Server::status_change(int status){
    if(status != 5)
    gamewindow->refresh(players, &block);
    this->status = status;
    //After changing the status, please emit the signal (status change)

    gamewindow->handleStatusChange(status);
}


void Server::start() {
    //Randomly select the current player() [Server -> Client GUI]

    int id = rand() % players.size();
    Player* player = current_player = players[id];
    initboard();
    gamewindow->setCurrentPlayer(id);
    for(int i =0 ; i < 40; ++i){
        Asset* a = dynamic_cast<Asset*>(block[i]);
        if (a != nullptr){
            player->add_asset(a);
            a->change_owner(player);
            a->update();
        }
        player = players[(id+i)%4];
    }
    //Wait a signal to roll the dice from Client GUI
    status_change(1);
}

//Define it as a slot (throw the dice only if the client sends the signal to do so)
void Server::roll_dice() {
//    int first = rand() % 6 + 1;
//    int second = rand() % 6 + 1;
    int first = 3;
    int second = 4;
    bool doubles = (first == second);
    if(doubles)
        ++double_count;
    else
        double_count = 0;

    //emit signal to GUI
    gamewindow->showDiceNumber(first, second);
    if(double_count == 3){
        current_player->movebyposition(10);
        current_player->stayin_jail();
        double_count =0;
        status_change(10);
    }else
        move(first + second);
}

void Server::move(int dice_sum){
    qDebug() << "moved";
    int prepos = current_player->get_playerposition();
    current_player->movebysteps(dice_sum);

    gamewindow->moveToken(current_player->get_playerposition());
    //gamewindow->refresh(players, block);

    if (prepos > current_player->get_playerposition()){
        current_player->set_money(current_player->get_money()+ 200);
    }

    trigger_event(dice_sum);
}


void Server::trigger_event(int dice_num){
//    int pos =2;
    int pos = current_player->get_playerposition();
    int signal = -1 ;
    Asset* asset = dynamic_cast<Asset*> (block[pos]);
    if (asset != nullptr && asset->get_owner() == nullptr){
        //buy
        qDebug() << "Player"<< current_player->get_playerid() <<"buy a house";
        status_change(2);

    }
    bool result = block[pos]->trigger_event(current_player, dice_num,signal);
        qDebug() << signal << "successful trigger";
        switch(signal){
            case 0:
                qDebug() << "go to jail";
                status_change(signal);
                break;
            case 3:
            {
                Asset* asset = dynamic_cast<Asset*>(block[pos]);
                // asset part
                if (asset != nullptr){
                    if (asset->get_owner() != current_player){
                        gamewindow->payToOtherPlayer(asset->get_owner()->get_playerid()
                                      , asset->get_rent());
                        status_change(signal);
                    }else
                        checkdouble();
                }
                qDebug()<< "give to owner";
                break;
            }
            case 4:
            {
                Charge* charge = dynamic_cast<Charge*>(block[pos]);
                if (charge != nullptr){
                 qDebug() << "pay to bank";
                    gamewindow->payToBank(charge->get_charge());
                }
                status_change(signal);
                break;
            }
            case 5:
            {
                SelectCard* sc = dynamic_cast<SelectCard*>(block[pos]);
                qDebug()<< "Draw a card";
                if (sc != nullptr){
                    Card* topcard = sc->get_card();
                    qDebug() << topcard->get_explanation();
                    gamewindow->setCardInstruction(sc->get_id(), topcard->get_explanation());
                    status_change(signal);
                }
                break;
            }
            default:
            qDebug()<< "nothing to do";
            status_change(6);
        }

}

void Server::drawn_after(){
//    gamewindow->refresh(players,&block);
    if (chance_block->get_trigger()){
        chance_block->reset_trigger();
        trigger_event(0);
    }else if(community_block->get_trigger()){

        community_block->reset_trigger();
        trigger_event(0);
    }else
        checkdouble();
}

void Server::checkdouble(){

    if(current_player->get_money() <0){
        status_change(20);
    }else if (double_count != 0 &&
        !current_player->is_injail()){
        status_change(1);
    }else
        status_change(10);
}


void Server::in_jail_action(int num){
    switch (num) {
        case 0:
        //pay
        {
            qDebug()<< "payed";
            current_player->pay_rent(nullptr,50);
            current_player->out_jail();
            roll_dice();
            break;
        }
        case 1:
        {
            qDebug()<< "used card";
            int card = -1;
            if (current_player->have_jailcard(card)){
                if(card == 0 || card == 2){
                    chance_block->add_jailcard();
                    current_player->use_jailcard(0);
                }else{
                    community_block->add_jailcard();
                    current_player->use_jailcard(1);
                }
                current_player->out_jail();
                roll_dice();
            }
            break;
        }
        case 2:
        {
            qDebug()<< "throw a double";
            int first = rand() % 6 + 1;
            int second = rand() % 6 + 1;
            gamewindow->showDiceNumber(first, second);
            if(first == second){
                current_player->out_jail();
                move(first+second);
            }else{
                current_player->stayin_jail();
                if (current_player->get_jail_turn() == 3){
                    in_jail_action(0);
                } else status_change(10);
            }
            break;
        }
    }
}


/*
 * Here, we should include the logic to check winning condition
 * in order to decide whether to continue game or not
 */
void Server::next_player(){
    int index = current_player->get_playerid();
    do {
        index = (index + 1) % players.size();
    } while (players[index]->islosed());

    current_player = players[index];
    double_count = 0;

    do {
        index = (index + 1) % players.size();
    } while (players[index]->islosed());

    if(current_player == players[index]) {
        gamewindow->setCurrentPlayer(index);
        gamewindow->setWarningMesseage(QString("CONGRATULATION!!\nPlayer ") + QString::number(index + 1) + "! YOU WIN.");
        status_change(31);
        return;
    }

    gamewindow->setCurrentPlayer(current_player->get_playerid());
    if(current_player->is_injail()) {
        bool canpay = (current_player->get_money()-50)>=0;
        int id;
        bool cancard = current_player->have_jailcard(id);
        gamewindow->updateInJailDialogue(canpay, cancard);

        status_change(0);
    } else {
        status_change(1);
    }

}


void Server::block_clicked_handler(int pos){
    switch(status){
        case 11:
        {
            Property* p = dynamic_cast<Property*>(block[pos]);
            if (p!= nullptr &&
                p->get_owner() == current_player)
            {
                if (!p->add_house())
                    p->add_hotel();
                qDebug() << "builded" << p->get_hotel() << p->get_house();
            }
            break;
        }
        case 12:
        {
            Asset* a = dynamic_cast<Asset*>(block[pos]);
            if (a != nullptr &&
                a->get_owner() == current_player&&
                !a->get_mortgage_status())
            {
                if (a->can_mortgage())
                    a->set_mortgage();
                else
                    gamewindow->setWarningMesseage("You have to sell all house and hotel in the same group of properties before mortgage");
                qDebug() << "mortgage" << a->get_mortgage_status();

            }
            break;
        }
        case 13:
        {
            Asset* a = dynamic_cast<Asset*>(block[pos]);
            if (a != nullptr &&
                a->get_owner() == current_player &&
                a->get_mortgage_status())
            {
                a->demortgage();
                qDebug() << "demortgage" << a->get_mortgage_status();

            }
            break;
        }
        case 14:
        {
            Property* p = dynamic_cast<Property*>(block[pos]);
            if (p!= nullptr &&
                p->get_owner() == current_player)
            {
                if (!p->sell_hotel())
                    p->sell_house();
                qDebug() << "builded" << p->get_hotel() << p->get_house();
            }
            break;
        }
    }
    gamewindow->refresh(players,&block);
}

void Server::purchaseProperty() {
    qDebug() << "Player"<< current_player->get_playerid() <<"buy a house";
    Asset* asset = dynamic_cast<Asset*> (block[current_player->get_playerposition()]);
    current_player->add_asset(asset);
    int fee = asset->get_cost_value();
    current_player->set_money(current_player->get_money() - fee);
    asset->change_owner(current_player);
    asset->update();
    qDebug() << "asset" << asset->get_owner()->get_playerid();

//    gamewindow->buyAsset(current_player->get_playerposition());

    checkdouble();
}

void Server::buildSomething() {
    if(status == 0 ||
       status == 1 ||
       status == 10){
        prev_status = status;
        status_change(11);
    }
}
void Server::mortgageSomething() {
    if(status == 0 || status == 1 || status == 10 || status == 20){
        prev_status = status;
        status_change(12);
    }
}
void Server::unmortgageSomething() {
    if(status == 0 ||
       status == 1 ||
       status == 10){
        prev_status = status;
        status_change(13);
    }
}

void Server::sellSomething() {
    if(status == 0 || status == 1 || status == 10  || status == 20) {
        prev_status = status;
        status_change(14);
    }
}

void Server::handleSimpleWidgetOKButton(int type) {
    if(type == 6) checkdouble();

    else if(type == 11 || type == 12 || type == 13 || type == 14){
        //Special case: player resolves the debt.
        if(prev_status == 20 && current_player->paydebts()) {
            checkdouble();
        } else {
            status = prev_status;
            status_change(status);
        }
    }
}

void Server::handleBankruptcy() {
    current_player->surrender();
    gamewindow->hideToken(current_player->get_playerid());
    next_player();
}
