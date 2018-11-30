#ifndef UTILITY_H
#define UTILITY_H
#include "asset.h"

class Utility : public Asset{

private:
    /*
     * 4 or 8
     */
    int rate_of_rent;
public:
    Utility(
            Block* (*block)[40],
            Player*owner,
            QString title,
            int cost
            );
    ~Utility();
    virtual void set_mortgage();
    virtual bool trigger_event(Player* player, int points);
    void set_rate(int rate);
    void update_ownrate();
};

#endif // UTILITY_H
