#include "utility.h"
#include <vector>
using namespace std;

Utility::Utility(
                 Block* (*block)[40],
                 Player*owner,QString title,
                 int cost
                 ):
    Asset(block,owner,title, cost),
    points(0),
    rate_of_rent(4)
{}

Utility::~Utility() {

}

void Utility::set_rate(int rate){
    rate_of_rent = rate;
}

void Utility::update_ownrate(){
    int num = 0;
    vector<Utility*> p_list;
    vector<Utility*>::iterator it;
    for(int i=0; i <40; ++i){
        Utility* p = dynamic_cast<Utility*>((*block)[i]);
        if (p != nullptr &&
            p->get_owner() == this->owner &&
            !mortgaged){
               num++;
               p_list.push_back(p);
        }
    }
    for(it = p_list.begin(); it != p_list.end() ; ++it)
          (*it)->set_rate(num*4);

}

bool Utility::trigger_event(Player* player, int points, int& signal){
    signal = 3;
    this->points = points;
    int rent = points*rate_of_rent;
    if (player != owner && !mortgaged){
        if (!player->pay_rent(owner,rent)){
            return false;
        }
    }
    return true;
}

void Utility::set_mortgage(){
    Asset::set_mortgage();
    update_ownrate();
}

int Utility::get_rent(){
    return rate_of_rent*points;
}

void Utility::update(){
    update_ownrate();
}
