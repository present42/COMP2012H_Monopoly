#include "asset.h"


Asset::Asset(int id,
             Block* (*block)[40],
             Player*owner,
             std::string title,
             int cost,
             int mortgage_value
             ):
Block(id,block),
owner(owner),
title(title),
cost(cost),
mortgage_value(mortgage_value),
mortgaged(false)
{}

void Asset::change_owner(Player* player){
    this->owner = player;
}
Player* Asset::get_owner(){
    return owner;
}
int Asset::get_assetcost(){
    return cost;
}
int Asset::get_assetmortgage(){
    return mortgage_value;
}

//void Asset::trigger_event(Player* player){

//}

