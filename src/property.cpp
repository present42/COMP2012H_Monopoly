#include "property.h"
#include <vector>
#include <QDebug>
#include "asset.h"
using namespace std;

Property:: Property(

         Block* (*block)[40],
         Player* owner,
         QString title ,
         int cost,
         int housecost,
         vector<int> rentlist,
         Group group):

    Asset(block,owner,title, cost),
    house(0),
    hotel(0),
    group(group),
    monopoly(0),
    housecost(housecost),
    rentlist(rentlist)
{
}

Property::~Property() {

}

int Property::get_housecost() const{
    return housecost;

}
int Property::get_house() const{
    return house;
}

int Property::get_hotel() const{
    return hotel;
}

int Property::get_rent() {
    int times = (monopoly && house ==0 && hotel ==0)? 2:1;
    if (hotel != 0)
        return rentlist[5]*times;

        return rentlist[house]*times;
}

bool Property::add_house(){
    if (hotel != 0 ||house+1 > MAX_HOUSE)
        return false;
    vector<int> list;
    for(int i=0; i <40; ++i){
        qDebug() << i;
        Property* p = dynamic_cast<Property*>((*block)[i]);
        if (p != nullptr &&
            p->group == this->group &&
            p->owner == this->owner){
            //
            if (p->get_monopoly() && p->get_house() < this->house)
                return false;
        }
    }
    house++;
    owner->set_money(owner->get_money()- housecost);
    return true;
}
bool Property::add_hotel(){
    if (hotel+1 > MAX_HOTEL)
        return false;
    vector<int> list;
    for(int i=0; i <40; ++i){
        Property* p = dynamic_cast<Property*>((*block)[i]);
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
    owner->set_money(owner->get_money()-housecost);
    return true;
}

bool Property::sell_house(){
    if (hotel != 0 || house == 0)
        return false;
    vector<int> list;
    for(int i=0; i <40; ++i){
        qDebug() << i;
        Property* p = dynamic_cast<Property*>((*block)[i]);
        if (p != nullptr &&
            p->group == this->group &&
            p->owner == this->owner){
            //
            if (p->get_monopoly() && (p->get_house() > this->house
                                     || p->get_hotel() ==1))
                return false;
        }
    }
    house--;
    owner->set_money(owner->get_money()+housecost/2);
    return true;
}

bool Property::sell_hotel(){
    if (hotel == 0)
        return false;

    hotel=0;
    house = 4;
    owner->set_money(owner->get_money()+housecost/2);
    return true;
}

int Property::sell_tobank(){
    int price = (hotel*5+house)*housecost/2;
    hotel =0;
    house =0;
    return price;
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
        Property* p = dynamic_cast<Property*>((*block)[i]);
        if (p != nullptr && p->group == this->group && !mortgaged){
            p_list.push_back(p);
            if(p->owner != this->owner){
                can_monopoly = false;
            }
        }
    }
    for (it = p_list.begin(); it != p_list.end(); ++it)
            (*it)->set_monopoly(can_monopoly);

}

bool Property::trigger_event(Player* player,int points, int& signal){
    signal =3;
    if (player!= owner && !mortgaged){
        int rent = ((int)monopoly+1)*rentlist[(house+hotel)];
        if (!player->pay_rent(owner, rent))
            return false;
    }
    return true;
}
bool Property::can_mortgage(){
    //sell all house
    if(monopoly){
        for(int i=0; i <40; ++i){
            Property* p = dynamic_cast<Property*>((*block)[i]);
            if (p != nullptr &&
                p->group == this->group &&
                p->owner == this->owner){
                if(p->get_house() !=0 ||
                   p->get_hotel() !=0){
                    return false;
                }
            }
        }
    }
    return Asset::can_mortgage();
}
void Property::set_mortgage(){
    Asset::set_mortgage();
    update_group_monopoly();
}

void Property::update(){
    update_group_monopoly();
}
