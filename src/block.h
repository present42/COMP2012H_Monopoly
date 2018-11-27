#ifndef BLOCK_H
#define BLOCK_H
#include "player.h"

// base base
class Block{
private:
    int id;
public:
    Block();
    virtual ~Block();
    virtual bool trigger_event(Player* player, int points) = 0 ;

};
#endif // BLOCK_H
