#ifndef CHARGE_H
#define CHARGE_H
#include "block.h"

class Charge : public Block{
    private:
        int charge;
    public:
        Charge(Block* (*block)[40], int charge);
        virtual ~Charge();
        virtual bool trigger_event(Player* player, int points);

};
#endif // CHARGE_H
