#ifndef RAILROAD_H
#define RAILROAD_H

#include "asset.h"


class Railroad : public Asset{

public:
    Railroad(Player* owner,
             std::string title,
             int cost,
             int mortage_value);

    void set_rent(int num);
    void update_ownrail();
    virtual bool trigger_event(Player* player, int points);

private:
    /*
     * rule: depend on the num rail
     * default 25
     */
    int rent;
};
#endif // RAILROAD_H
