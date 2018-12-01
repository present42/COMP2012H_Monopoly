#include "gotojail.h"

GotoJail::GotoJail(Block* (*block)[40]):
Block(block)
{

}
GotoJail::~GotoJail(){

}

bool GotoJail::trigger_event(Player* player, int points){
    player->movebyposition(10);
    player->stayin_jail();
    return true;
}
