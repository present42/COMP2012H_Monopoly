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

//        qDebug() << type << explanation;
        Community_chest.push_back(new Card(id,explanation,type));

    }
    file.close();

    chance_block = new SelectCard(&block, 0, players, Chance);
    community_block = new SelectCard(&block, 1,  players , Community_chest);

    //2, 17, 33 cc
    block[2] = block [17] = block [33] = community_block;
    //7, 22, 36 c
    block[7] = block [22] = block [36] = chance_block;


}

void Server::add_player(Player* new_player) {
    if(players.size() < 4) {
        new_player->set_money(1500);
        players.push_back( new_player);
        emit init_player(new_player->get_playerid());
    } else return;
}

// Move to other places
// Receive Money from Bank


/*
 * [Required signals to update GUI]
 *
 * Pay to bank event (Income tax, Property tax ..)
 * >>payToBank(int amount)
 *
 * Move to other places
 * >>
 *
 * Receive Money from Bank
 *
 *
 *
 */

/*
 * [Suggestion on Game Flow]
 * This function is called when the clients agree to start (all click the button)
 * Before this function is called, all participating players should be initiated
 *
 * <<Status Indicator>>
 * 0 : jail
 * 1 : Before rolling the dice
 *

 * 2 : Buy or Auction event
 * 3 : Pay rent event (Player A -> Player B) B rent
 * 5 : card

 *
 * 10 : Before ending his turn
 *
 * #1 : build
 * #2 : mortgage
 * #3 : unmortgage
 * #4 : trade
 */
void Server::status_change(int status){
    this->status = status;
    //After changing the status, please emit the signal (status change)
    emit status_changed(status);
}


void Server::start() {
    //Randomly select the current player() [Server -> Client GUI]

    int id = rand() % players.size();
    current_player = players[id];
    initboard();
    emit next(id);

    //Wait a signal to roll the dice from Client GUI
    status_change(1);
}

//Define it as a slot (throw the dice only if the client sends the signal to do so)
void Server::roll_dice() {
    int first = rand() % 6 + 1;
    int second = rand() % 6 + 1;

    bool doubles = (first == second);
    if(doubles)
        ++double_count;
    else
        double_count = 0;

    //emit signal to GUI
    emit dice_thrown(first, second);
    if(double_count == 3){
        current_player->movebyposition(10);
        current_player->stayin_jail();
        double_count =0;
        status_change(0);
    }else
        move(first + second);
}

void Server::move(int dice_sum){
    qDebug() << "moved";
    int prepos = current_player->get_playerposition();
    current_player->movebysteps(dice_sum);

    emit player_moved(current_player->get_playerposition());

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
        qDebug() << "buy a house";
        emit asset_bought(pos);
        status_change(2);

    }else if (block[pos]->trigger_event(current_player, dice_num,signal)){
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
                        emit pay_rent(asset->get_owner()->get_playerid()
                                      , asset->get_rent());
                    }
                }
                qDebug()<< "give to owner";
                status_change(signal);
                break;
            }
            case 4:
            {
                Charge* charge = dynamic_cast<Charge*>(block[pos]);
                if (charge != nullptr){
                 qDebug() << "pay to bank";
                    emit pay_bank(charge->get_charge());
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
                    emit card_drawn(sc->get_id(), topcard->get_explanation());
                    status_change(signal);
                    //if (sc->get_trigger()){
                    //    sc->reset_trigger();
                    //    trigger_event(0);
                    //}

                }
                break;
            }
            default:
            qDebug()<< "nothing to do";
            status_change(6);
        }
    }
    else
    {
        qDebug()<< "fail";
        //no money
//        status_change(4);
    }


}

void Server::checkdouble(){
    if (double_count != 0){
        status_change(1);
    }else
        status_change(10);
}

void Server::bankruptcy(){
    current_player->bankruptcy();
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

    if (current_player == players[index]){
        //end game
        return;
    }else{
        current_player = players[index];
        double_count = 0;
    }
    emit next(current_player->get_playerid());
    status_change(1);
}

void Server::purchaseProperty() {
    Asset* asset = dynamic_cast<Asset*> (block[current_player->get_playerposition()]);
    current_player->add_asset(asset);
    int fee = asset->get_cost_value();
    current_player->set_money(current_player->get_money() - fee);
    asset->change_owner(current_player);

    qDebug()<< current_player->get_money();
    emit pay_bank(fee);
    status_change(10);
}
