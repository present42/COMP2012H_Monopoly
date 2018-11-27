#ifndef PLAYER_H
#define PLAYER_H
#include "token.h"

class Player{
private:
    int id;
    int money;
    int position;
    // -1 mean not in jail
    int jail_turn;
    bool passed_GO;
    Token token;

public:

    Player(int id,Token token);

    //asset part
    // false mean not enough money
    bool pay_rent(Player* player,int rent);
    void set_money(int money);
    int get_money() const;

    //movement
    void movebysteps(int steps);
    void movebyposition(int position);

    //status
    int get_playerid() const;
    int get_playerposition() const;
    Token get_playertoken() const;

    //go
    bool is_passed_GO() const;
    void set_passed_GO(bool);

    //jail
    bool is_injail() const;
    int  injail_turn() const;
    void out_jail();
    void stayin_jail();
};

#endif // PLAYER_H
