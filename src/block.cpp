#include "block.h"

Block::Block(Block* (*block)[40]):
    block(block)
{

}

Block::~Block() {

}

bool Block::trigger_event(Player* player, int points){
    return true;
}


