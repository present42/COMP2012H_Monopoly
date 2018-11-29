#include "railroad.h"
#include <vector>
using namespace std;
Railroad::Railroad(Player*owner,std::string title, int cost, int mortgage_value):
    Asset(owner,title, cost,mortgage_value),
    rent(25)
{
}


void Railroad::set_rent(int num){
    rent *= num;
}

void Railroad::update_ownrail(){
    /*
     * Assume we have a block* (*block)[40]
     */
    int num;
    Block* (*block)[40] = nullptr;
    vector<Railroad*> p_list;
    for(int i=0; i <40; ++i){
        Railroad* p = dynamic_cast<Railroad*>(*block[i]);
        if (p != nullptr &&
            p->get_owner() == this->owner){
               p_list.push_back(p);
        }
    }

}

bool Railroad::trigger_event(Player* player, int points){
    if (player != owner && !player->pay_rent(owner,rent)){
            return false;
    }
    return true;
}

