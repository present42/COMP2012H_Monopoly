#ifndef RAILROAD_H
#define RAILROAD_H

#include "asset.h"


class Railroad : public Asset {

public:
    Railroad(
             Block* (*block)[40],
             Player* owner,
             QString title,
             int cost
             );
    ~Railroad();
    void set_rent(int num);
    void update_ownrail();
    int get_rent();
    virtual void set_mortgage();
    virtual bool trigger_event(Player* player, int points, int& signal);

private:
    /*
     * rule: depend on the num rail
     * default 25
     */
    int rent = 25;
};
#endif // RAILROAD_H
