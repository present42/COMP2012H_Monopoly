#include "utility.h"


Utility::Utility(Player*owner,std::string title, int cost, int mortgage_value):
    Asset(owner,title, cost,mortgage_value),
    rate_of_rent(4)
{}

bool Utility::trigger_event(Player* player, int points){
    int rent = points*rate_of_rent;
    if (player != owner){
        if (!player->pay_rent(owner,rent)){
            return false;
        }
    }
    return true;
}
void Utility::set_rate(int rate){
    rate_of_rent = rate;
}

