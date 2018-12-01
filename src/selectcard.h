#ifndef SELECTCARD_H
#define SELECTCARD_H

#include "block.h"
#include "card.h"
#include <vector>

using namespace std;
class SelectCard : public Block{

    private:
    int id;
    int index;
    bool trigger_again;
    Card* tempdiscard;
    vector<Player*> players;
    vector<Card*> carddeck;

public:
    SelectCard(Block* (*block)[40],
               int id,
               vector<Player *> players,
               vector<Card*> carddeck);

    virtual ~SelectCard();
    virtual bool trigger_event(Player* player, int points);
    void suffle();
    void add_jailcard();
    bool get_trigger() const;
    void reset_trigger();


};
#endif // SELECTCARD_H
