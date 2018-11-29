#ifndef BLOCK_H
#define BLOCK_H
#include "player.h"

// base base
class Block{
protected:
    int id;
    Block* (*block)[40];
public:
    Block(int id, Block* (*block)[40]);
    virtual ~Block();
    virtual bool trigger_event(Player* player, int points) = 0 ;

};
#endif // BLOCK_H
