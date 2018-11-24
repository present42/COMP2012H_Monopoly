#ifndef PLAYER_H
#define PLAYER_H
#include "token.h"

class Player{
private:
    int id;
    int asset;
    int position;
    // -1 mean not in jail
    int jail_turn;
    bool passed_GO;
    Token token;

public:

    Player(int id,Token token);

    void movebysteps(int steps);
    void movebyposition(int position);

    int get_playerid() const;
    int get_playerposition() const;
    Token get_playertoken() const;

    bool is_passed_GO() const;
    void set_passed_GO(bool);

    bool is_injail() const;
    int  injail_turn() const;
    void out_jail();
    void stayin_jail();
};

#endif // PLAYER_H
