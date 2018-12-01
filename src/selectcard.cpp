#include "selectcard.h"
#include "property.h"
#include "algorithm"
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

bool SelectCard::trigger_event(Player* player, int points){
    trigger_again = false;
    if (index > carddeck.size()){
        suffle();
        index = 0;
    }
    Card* card = carddeck[index];
    QString string = card->get_type();
    QStringList list = (string.left(string.length() -1)).split('(');
    QStringList Case;
    index++;
    Case << "P" << "P2" << "R" << "M" << "F";
    switch(Case.indexOf(list[0])){
        case 0:
        {
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
          player->set_money(player->get_money()+list[1].toInt());
          break;
        }
        case 3:
        //move
        {
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
            if (prepos < nowpos)
                player->set_money(player->get_money()+200);
            trigger_again = true;
            break;
        }
        case 4:
        for(vector<Card*>::iterator p = carddeck.begin();
            p!= carddeck.end() ; ++p){
            if ((*p)->get_type() == card->get_type()){
                tempdiscard = *p;
                carddeck.erase(p);
            }
        }
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