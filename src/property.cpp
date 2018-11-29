#include "property.h"
#include <vector>
using namespace std;

Property:: Property(
         int id,
         Block* (*block)[40],
         Player* owner,
         std::string title ,
         int cost,
         int mortgage_value,
         int rentlist[6],
         Group group):
    Asset(id,block,owner,title, cost,mortgage_value),
    house(0),
    hotel(0),
    group(group),
    monopoly(0)
{
    for(int i=0; i<6 ;++i)
        this->rentlist[i] = rentlist[i];
}
int Property::get_house(){
    return house;
}

int Property::get_hotel(){
    return hotel;
}

int Property::get_rent(){
    if (hotel != 0)
        return rentlist[5];

        return rentlist[house];
}

bool Property::add_house(){
    if (hotel != 0 ||house+1 > MAX_HOUSE)
        return false;
    vector<int> list;
    /*
     * Assume we have a block* (*block)[40]
     */

    Block* (*block)[40] = nullptr;
    for(int i=0; i <40; ++i){
        Property* p = dynamic_cast<Property*>(*block[i]);
        if (p != nullptr &&
            p->group == this->group &&
            p->owner == this->owner){
            //
            if (p->get_monopoly() && p->get_house() < this->house)
                return false;
        }
    }
    house++;
    return true;
}
bool Property::add_hotel(){
    if (hotel+1 > MAX_HOTEL)
        return false;
    vector<int> list;
    /*
     * Assume we have a block* (*block)[40]
     */

    for(int i=0; i <40; ++i){
        Property* p = dynamic_cast<Property*>(*block[i]);
        if (p != nullptr &&
            p->group == this->group &&
            p->owner == this->owner){
            //
            if (p->get_monopoly() && (p->get_house() < this->house &&
                                      p->get_hotel() == 0))
                return false;
        }
    }
    house = 0;
    hotel++;
    return true;
}

bool Property::get_monopoly() const{
    return monopoly;
}

void Property::set_monopoly(bool monopoly){
    this->monopoly = monopoly;
}

void Property::update_group_monopoly(){
    /*
     * Assume we have a block* (*block)[40]
     */
    bool can_monopoly = true;
    vector<Property*> p_list;
    vector<Property*>::iterator it;
    for(int i=0; i <40; ++i){
        Property* p = dynamic_cast<Property*>(*block[i]);
        if (p != nullptr && p->group == this->group){
            p_list.push_back(p);
            if(p->owner != this->owner){
                can_monopoly = false;
            }
        }
    }
    for (it = p_list.begin(); it != p_list.end(); ++it)
            (*it)->set_monopoly(can_monopoly);

}

bool Property::trigger_event(Player* player,int points){
    if (player!= owner){
        int rent = ((int)monopoly+1)*rentlist[(house+hotel)];
        if (!player->pay_rent(owner, rent))
            return false;
    }
    return true;
}


