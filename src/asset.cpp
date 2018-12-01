#include "asset.h"


Asset::Asset(
             Block* (*block)[40],
             Player*owner,
             QString title,
             int cost
             ):
    Block(block),
    owner(owner),
    title(title),
    cost(cost),
    mortgage_value(cost/2)
{}

Asset::~Asset() {

}

void Asset::change_owner(Player* player){
    this->owner = player;
}

Player* Asset::get_owner() const{
    return owner;
}

int Asset::get_cost_value() const{
    return cost;
}

int Asset::get_mortgage_value()  const{
    return mortgage_value;
}

bool Asset::get_mortgage_status() const{
    return mortgaged;
}


void Asset::set_mortgage(){
    mortgaged = true;
    owner->set_money(owner->get_money()+mortgage_value);
}

void Asset::demortgage(){
    mortgaged = false;
    owner->set_money(owner->get_money()-mortgage_value*1.1);
}


bool Asset::trigger_event(Player* player, int points){
   return Block::trigger_event(player,points);
}



