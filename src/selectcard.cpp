#include "selectcard.h"
#include "property.h"
#include "algorithm"
#include "QDebug"
#include "QStringList"

SelectCard::SelectCard(
                       Block* (*block)[40],
                       int id,
                       vector<Player*> players ,
                       vector<Card*> carddeck)
    :Block(block),
     id(id),
     index(0),
     trigger_again(false),
     selectedcard(nullptr),
     tempdiscard(nullptr),
     players(players),
     carddeck(carddeck)
{
    suffle();
}

SelectCard::~SelectCard(){
    vector<Card*>::iterator p ;
    for(p = carddeck.begin(); p != carddeck.end(); ++p )
        delete (*p);
}

int random(int i ) {return std::rand()%i;}
void SelectCard::suffle(){
    random_shuffle(carddeck.begin(),carddeck.end(),random);
}

bool SelectCard::trigger_event(Player* player, int points, int& signal){
    trigger_again = false;
    signal = 5;
    if (index == carddeck.size()-1){
        suffle();
        index = 0;
    }
    Card* card = selectedcard = carddeck[index];
    QString string = card->get_type();
    QStringList list = (string.left(string.length() -1)).split('(');
    QStringList Case;
    Case << "P" << "P2" << "R" << "R2"<< "M" << "F";
    index++;
    switch(Case.indexOf(list[0])){
        case 0:
        {
            qDebug() << "card event P";
            int fee =0;
            if (list[1] == "-1" || list[1] == "-2"){
                int housenum =0;
                int hotelnum =0;
                vector<Asset*> alist = player->get_assetlist();
                for (vector<Asset*>::iterator p = alist.begin();
                     p != alist.end() ; ++p)
                {
                   Property* property = dynamic_cast<Property*>(*p);
                   if (property != nullptr){
                       housenum+= property->get_house();
                       hotelnum+= property->get_hotel();
                    }
                }
                if (list[1] == "1")
                fee = housenum*25 + hotelnum*100;
                else
                fee = housenum*40 + hotelnum*115;
            }else
                fee = list[1].toInt();
            return player->pay_rent(nullptr, fee);
        }
        case 1:
        {
        qDebug() << "card event P2";
        int fee = list[1].toInt();
        for (vector<Player*>::iterator p  = players.begin() ;
             p != players.end(); ++p){
            if (*p != player){
                player->pay_rent(*p,fee);
            }
        }
        return (player->get_money()<0)? false: true;
        }
        case 2:
        {
          qDebug() << "card event R";
          player->set_money(player->get_money()+list[1].toInt());
          break;
        }
        case 3:
        {
            qDebug() << "card event R2";
            int fee = list[1].toInt();
            for (vector<Player*>::iterator p  = players.begin() ;
                 p != players.end(); ++p){
                if (*p != player){
                    (*p)->pay_rent(player,fee);
                }
            }
            break;
        }
        case 4:
        //move
        {
            qDebug() << "card event M";
            int prepos = player->get_playerposition();
            switch(list[1].toInt()){
                // omit case 41 ,42 first
                case 41:
                break;
                case 42:
                //send signal
                break;
                case 10:
                    player->movebyposition(10);
                    player->stayin_jail();
                return true;
                case -3:
                    player->movebysteps(-3);
                break;
                default:
                    player->movebyposition(list[1].toInt());
            }
            int nowpos = player->get_playerposition();

            if (nowpos < prepos &&
                list[1].toInt()!= -3 &&
                list[1].toInt()!= 10){
                qDebug()<< "player receive the money" << player->get_playerid();
                player->set_money(player->get_money()+200);
                }
            trigger_again = true;
            break;
        }
        case 5:
        qDebug() << "card event F";
        for(vector<Card*>::iterator p = carddeck.begin();
            p!= carddeck.end() ; ++p){
            if ((*p)->get_type() == card->get_type()){
                tempdiscard = *p;
                carddeck.erase(p);
            }
        }
        qDebug() << "card event F";
        player->keep_jailcard(id);
    }
    return true;
}

void SelectCard::reset_trigger(){
    trigger_again = false;
}

bool SelectCard::get_trigger() const{
    return trigger_again;
}

void SelectCard::add_jailcard(){
    carddeck.push_back(tempdiscard);
    tempdiscard = nullptr;
}

int SelectCard::get_id() const{
    return id;
}

Card* SelectCard::get_card() const{
    return selectedcard;
}
