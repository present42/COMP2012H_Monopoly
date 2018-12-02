#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "token.h"
#include "card.h"

using namespace std;

class Asset;

class Block;

class Player{

private:
    int id;
    int money;
    int position;
    vector<Asset*> assetlist;
    bool jailcardlist[2];
    int jail_turn;
    bool losed;
    Token token;

public:

    Player(int id, Token token);

    //asset part
    void add_asset(Asset* asset);
    vector<Asset*> get_assetlist();
    void remove_asset(Asset* asset);
    int get_totalhouse();
    int get_totalhotel();

    // false mean not enough money
    bool pay_rent(Player* player,int rent);
    void set_money(int money);
    int get_money() const;
    int get_jail_turn();

    //movement
    void movebysteps(int steps);
    void movebyposition(int position);

    //status
    int get_playerid() const;
    int get_playerposition() const;
    Token get_playertoken() const;


    //jail
    bool is_injail() const;
    int  injail_turn() const;
    void out_jail();
    void stayin_jail();

    //0 ,1 ,2 = both
    bool have_jailcard(int &id);
    void use_jailcard(int id);
    void keep_jailcard(int id);


    //determine lose or not
    // if asset_value + money + jailcard < 0 gg
    bool willlose();
    void surrender();
    bool islosed();
    void bankruptcy();

};

#endif // PLAYER_H
