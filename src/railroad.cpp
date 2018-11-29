#include "railroad.h"
#include <vector>
using namespace std;
Railroad::Railroad(int id,
                   Block* (*block)[40],Player*owner,std::string title, int cost, int mortgage_value):
    Asset(id, block, owner, title, cost, mortgage_value)
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
            p->get_owner() == this->owner){
               num++;
               p_list.push_back(p);
        }
    }
    for(it = p_list.begin(); it != p_list.end() ; ++it)
          (*it)->set_rent(num);
}

bool Railroad::trigger_event(Player* player, int points){
    if (player != owner && !player->pay_rent(owner,rent)){
            return false;
    }
    return true;
}

