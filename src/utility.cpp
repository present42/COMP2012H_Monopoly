#include "utility.h"
#include <vector>
using namespace std;

Utility::Utility(int id,
                 Block* (*block)[40],
                 Player*owner,std::string title,
                 int cost,
                 int mortgage_value):
    Asset(id,block,owner,title, cost,mortgage_value),
    rate_of_rent(4)
{}

void Utility::set_rate(int rate){
    rate_of_rent = rate;
}

void Utility::update_ownrate(){
    int num = 0;
    vector<Utility*> p_list;
    vector<Utility*>::iterator it;
    for(int i=0; i <40; ++i){
        Utility* p = dynamic_cast<Utility*>(*block[i]);
        if (p != nullptr &&
            p->get_owner() == this->owner){
               num++;
               p_list.push_back(p);
        }
    }
    for(it = p_list.begin(); it != p_list.end() ; ++it)
          (*it)->set_rate(num*4);

}

bool Utility::trigger_event(Player* player, int points){
    int rent = points*rate_of_rent;
    if (player != owner){
        if (!player->pay_rent(owner,rent)){
            return false;
        }
    }
    return true;
}
