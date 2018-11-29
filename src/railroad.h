#ifndef RAILROAD_H
#define RAILROAD_H

#include "asset.h"


class Railroad : public Asset {

public:
    Railroad(int id,
             Block* (*block)[40],
             Player* owner,
             std::string title,
             int cost,
             int mortage_value);
    ~Railroad();
    void set_rent(int num);
    void update_ownrail();
    virtual bool trigger_event(Player* player, int points);

private:
    /*
     * rule: depend on the num rail
     * default 25
     */
    int rent = 25;
};
#endif // RAILROAD_H
