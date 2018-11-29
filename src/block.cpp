#include "block.h"

Block::Block(int id, Block* (*block)[40]):
    id(id),
    block(block)
{
}

Block::~Block() {

}
