#ifndef SELECTCARD_H
#define SELECTCARD_H

#include "block.h"
#include "card.h"
#include <deque>
class SelectCard : public Block{

    private:
    Card* selectedCard;
    int index;
    deque<Card*> carddeque;

public:
    SelectCard(Block* (*block)[40]);
    virtual ~SelectCard();
    virtual bool trigger_event(Player* player, int points);
    void suffle();


};
#endif // SELECTCARD_H
