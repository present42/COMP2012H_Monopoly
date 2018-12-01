#include "charge.h"

Charge::Charge(Block* (*block)[40], int charge):
Block(block),
charge(charge)
{
}

Charge::~Charge(){

}

bool Charge::trigger_event(Player* player, int points, int& signal){
    signal = 4;
    return player->pay_rent(nullptr, charge);
}

int Charge::get_charge() const{
    return charge;
}

