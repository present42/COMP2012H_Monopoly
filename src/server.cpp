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
        qDebug() << pos << cost << housecost << title << rentlist << group;
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
        QString type = obj["type"].toString();
        QString explanation = obj["explanation"].toString();
        qDebug() << type << explanation;
        Chance.push_back(new Card(explanation,type));

    }

    file.close();

    //init community_chest
    file.setFileName(":/res/json/community_chest_card.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    Json = QJsonDocument::fromJson(file.readAll(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        qDebug() << jsonError.errorString();
    }

    list = Json.toVariant().toList();
    for(QList<QVariant>::iterator p = list.begin();p != list.end(); ++p){
        QJsonObject obj = p->toJsonObject();
        QString type = obj["type"].toString();
        QString explanation = obj["explanation"].toString();
        qDebug() << type << explanation;
        Community_chest.push_back(new Card(explanation,type));
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
        players.push_back( new_player);
        emit init_player(new_player->get_playerid());
    } else return;
}

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
 * 3 : Pay rent event (Player A -> Player B)
 * 4 : Pay to bank event (Income tax, Property tax ..)
 * 5 : Move to other places
 * 6 : Receive Money from Bank
 *
 * 7 : Open Card event
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

    move(first + second);

}

void Server::move(int dice_sum){
    int prepos = current_player->get_playerposition();
    current_player->movebysteps(dice_sum);

    emit player_moved(current_player->get_playerposition());

    if (prepos > current_player->get_playerposition()){
        current_player->set_money(current_player->get_money()+ 200);
    }

    trigger_event(dice_sum);
}


void Server::trigger_event(int dice_num){

    int pos = current_player->get_playerposition();

    Asset* asset = dynamic_cast<Asset*> (block[pos]);
    if (asset != nullptr && asset->get_owner() == nullptr){
        status_change(2);
    }else if (block[pos]->trigger_event(current_player, dice_num)){
        SelectCard* sc = dynamic_cast<SelectCard*>(block[pos]);
        if (sc != nullptr && sc->get_trigger()){
            sc->reset_trigger();
            trigger_event(0);
        } else if (current_player->is_injail()){
            status_change(0);
        }else if(current_player->willlose()){
             //gg
            bankruptcy();
        }else
            status_change(3);
    }else
        status_change(4);
}

void Server::bankruptcy(){
    current_player->bankruptcy();
}

/*
 * Here, we should include the logic to check winning condition
 * in order to decide whether to continue game or not
 */
void Server::next_player(){
    if (double_count == 0){
        int index = current_player->get_playerid();
        do {
            index = (index + 1) % players.size();
        }while (players[index]->islosed());

        if (current_player == players[index]){
            //end game
            return;
        }else{
            current_player = players[index];
            double_count = 0;
        }
    }

    emit next(current_player->get_playerid());
    status_change(1);
}

void Server::purchaseProperty() {

}
