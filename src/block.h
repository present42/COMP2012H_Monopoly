#ifndef BLOCK_H
#define BLOCK_H
#include "player.h"

// base base
class Block{
    public:
        Block(Block* (*block)[40]);
        virtual ~Block();
        virtual bool trigger_event(Player* player, int points);

    protected:
        int id;
        Block* (*block)[40];

};
#endif // BLOCK_H
