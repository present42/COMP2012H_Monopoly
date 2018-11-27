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
    Utility(Player*owner,std::string title, int cost, int mortgage_value);
    virtual bool trigger_event(Player* player, int points);
    void set_rate(int rate);
};

#endif // UTILITY_H
