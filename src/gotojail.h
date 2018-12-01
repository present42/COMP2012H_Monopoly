#ifndef GOTOJAIL_H
#define GOTOJAIL_H

#include "block.h"

class GotoJail : public Block{
public:
    GotoJail(Block* (*block)[40]);
    ~GotoJail();
    virtual bool trigger_event(Player* player, int points);

};

#endif // GOTOJAIL_H
