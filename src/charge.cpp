#include "charge.h"

Charge::Charge(Block* (*block)[40], int charge):
Block(block),
charge(charge)
{
}

bool Charge::trigger_event(Player* player, int points){
    if(player->get_money()- charge <0)
        return false;
    player->set_money(player->get_money() - charge);
    return true;
}

