#include <cstdlib>
#include <ctime>
#include "server.h"
#include <QtDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QString>
#include <QFile>
#include "ui/rolldicewidget.h"
#include "token.h"

using namespace std;

Server::Server():
  current_player(nullptr),
  double_count(0)
{
    srand(time(0));
    //init the board here


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
//        qDebug() << pos << cost << housecost << title << rentlist << group;
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





}

Server::~Server() {

}

void Server::add_player(Player* new_player) {
    if(num_player < 4) {
        players[num_player++] = new_player;
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
 * 2 : buy or auction
 * 3 : follow instruction (pay rent, pay .. to bank, receive money from bank, move to somewhere)
 * 4 : not enough money
 * 5 : Before ending his turn
 *
 * #1 : build
 * #2 : mortgage
 * #3 : unmortgage
 * #4 : trade
 */
void Server::status_change(int status){
    this->status = status;
    //After changing the status, please emit the signal (status change)
    emit emit_status(status);
}


void Server::start() {
    //Randomly select the current player() [Server -> Client GUI]
    current_player = players[rand() % 4];
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
    emit_dice(first,second);
}

void Server::move(int dice_sum){
    current_player->movebysteps(dice_sum);
    trigger_event(dice_sum);

    if(double_count > 0) {
        //Set status to 1 (Waiting for the current player to throw the dice)
    } else {
        //Set status to the last status
    }
}


void Server::trigger_event(int dice_num){
    if(current_player->is_passed_GO()){
        //pop up + money
        current_player->set_passed_GO(false);
    }
    int pos = current_player->get_playerposition();

    Asset* asset = dynamic_cast<Asset*> (block[pos]);
    if (asset != nullptr && asset->get_owner() == nullptr){
        emit_status(2);
    }

    if (block[pos]->trigger_event(current_player, dice_num)){
        emit_status(3);
    }else
        emit_status(4);

}

/*
 * Here, we should include the logic to check winning condition
 * in order to decide whether to continue game or not
 */
void Server::next_player(){
    if (double_count == 0){
        int index = (current_player->get_playerid() + 1) % 4;
        current_player = players[index];
        double_count = 0;
    }
    emit_next();
}

GameWindow* Server::get_game_window() {
    return game_window;
}


void Server::startGUI() {
    game_window = new GameWindow(nullptr);
}

//void Server::init_board(){

//    //Properties
//    block[1] = new Property(1,&block,nullptr,"",60,30,50,{2,10,30,90,160,250},Property::Brown);
//    block[3] = new Property(3,&block,nullptr,"",60,30,50,{4,20,60,180,320,450},Property::Brown);
//    block[6] = new Property(6,&block,nullptr,"",100,50,50,{6,30,90,270,400,450},Property::LightBlue);
//    block[8] = new Property(8,&block,nullptr,"",100,50,50,{6,30,90,270,400,450},Property::LightBlue);
//    block[9] = new Property(9,&block,nullptr,"",120,60,50,{8,40,100,300,450,600},Property::LightBlue);
//    block[11] = new Property(11,&block,nullptr,"",140,70,100,{10,50,150,450,625,750},Property::Pink);
//    block[13] = new Property(13,&block,nullptr,"",140,70,100,{10,50,150,450,625,750},Property::Pink);
//    block[14] = new Property(14,&block,nullptr,"",160,80,100,{12,60,180,500,700,900},Property::Pink);
//    block[16] = new Property(16,&block,nullptr,"",180,90,100,{14,70,200,550,750,950},Property::Orange);
//    block[18] = new Property(18,&block,nullptr,"",180,90,100,{14,70,200,550,750,950},Property::Orange);
//    block[19] = new Property(19,&block,nullptr,"",200,100,100,{16,80,220,600,800,1000},Property::Orange);
//    block[21] = new Property(21,&block,nullptr,"",220,110,150,{18,90,250,700,875,1050},Property::Red);
//    block[23] = new Property(23,&block,nullptr,"",220,110,150,{18,90,250,700,875,1050},Property::Red);
//    block[24] = new Property(24,&block,nullptr,"",240,120,150,{20,100,300,750,925,1100},Property::Red);
//    block[26] = new Property(26,&block,nullptr,"",260,130,150,{22,110,330,800,975,1150},Property::Yellow);
//    block[27] = new Property(27,&block,nullptr,"",260,130,150,{22,110,330,800,975,1150},Property::Yellow);
//    block[29] = new Property(29,&block,nullptr,"",280,140,150,{24,120,360,850,1025,1200},Property::Yellow);
//    block[31] = new Property(31,&block,nullptr,"",300,150,200,{26,130,390,900,1100,1275},Property::Green);
//    block[32] = new Property(32,&block,nullptr,"",300,150,200,{26,130,390,900,1100,1275},Property::Green);
//    block[34] = new Property(34,&block,nullptr,"",320,160,200,{28,150,450,1000,1200,1400},Property::Green);
//    block[37] = new Property(37,&block,nullptr,"",350,175,200,{35,175,500,1100,1300,1500},Property::Blue);
//    block[39] = new Property(39,&block,nullptr,"",400,200,200,{50,200,600,1400,1700,2000},Property::Blue);

//    //railroad
//    for(int i :{5,15,25,35})
//    block[i] = new Railroad(i,&block,nullptr,"",200,100);

//}


