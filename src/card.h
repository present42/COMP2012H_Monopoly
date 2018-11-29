#ifndef CARD_H
#define CARD_H

#include "block.h"
#include <string>
using namespace std;

class Card : public Block{
    protected:
    string description;

    public:

    Card();
    ~Card();
    virtual bool trigger_event(Player* player, int points);
};
#endif // CARD_H
