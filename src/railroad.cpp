#include "railroad.h"
#include <vector>
using namespace std;
Railroad::Railroad(
                   Block* (*block)[40],
                   Player*owner,QString title, int cost):
    Asset(block, owner, title, cost)
{
}

Railroad::~Railroad() {

}


void Railroad::set_rent(int num){
    rent *= num;
}

void Railroad::update_ownrail(){
    /*
     * Assume we have a block* (*block)[40]
     */
    int num = 0;
    vector<Railroad*> p_list;
    vector<Railroad*>::iterator it;
    for(int i=0; i <40; ++i){
        Railroad* p = dynamic_cast<Railroad*>(*block[i]);
        if (p != nullptr &&
            p->get_owner() == this->owner &&
            !mortgaged){
               num++;
               p_list.push_back(p);
        }
    }
    for(it = p_list.begin(); it != p_list.end() ; ++it)
          (*it)->set_rent(num);
}

bool Railroad::trigger_event(Player* player, int points){
    if (player != owner && !mortgaged
            && !player->pay_rent(owner,rent)){
            return false;
    }
    return true;
}

void Railroad::set_mortgage(){
    Asset::set_mortgage();
    update_ownrail();
}

