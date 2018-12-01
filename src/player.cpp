#include "player.h"
#include "asset.h"
#include "property.h"
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

Player::Player(int id, Token token):
  id(id),
  money(0),
  position(0),
  jail_turn(0),
  losed(false),
  token(token)
{
    jailcardlist[0] = false;
    jailcardlist[1] = false;
}

void Player::add_asset(Asset * asset){
    assetlist.push_back(asset);
}

void Player::remove_asset(Asset* asset){
    vector<Asset*>::iterator p = find(assetlist.begin(), assetlist.end(), asset);
    assetlist.erase(p);
}

vector<Asset*> Player::get_assetlist(){
    return assetlist;
}


bool Player::pay_rent(Player* player, int rent){
    if (player != nullptr)
        player->set_money(get_money()+rent);

    money-=rent;
    if (money < 0)
        return false;
    return true;
}

void Player::set_money(int money){
    this->money = money;
}

int Player::get_money() const{
    return money;
}

void Player::movebysteps(int steps){
    position += steps;
    if (position < 0){
        position += 40;
    }else if (position > 39){
        position %= 40;
    }
}
void Player::movebyposition(int position){
    this->position = position;
}

int Player::get_playerid() const{
    return id;
}

int Player::get_playerposition() const{
    return position;
}

Token Player::get_playertoken() const{
    return token;
}

bool Player::is_injail() const{
    return (jail_turn== -1)? false: true;
}


void Player::out_jail(){
    jail_turn = -1;
}

void Player::stayin_jail(){
    jail_turn += 1;
}

int Player::get_jail_turn() {
    return jail_turn;
}

void Player::use_jailcard(int id){
    jailcardlist[id] = false;
}

void Player::have_jailcard(int &id){
    if(jailcardlist[0] && jailcardlist[1])
        id = 2;
    else if (jailcardlist[0])
        id = 0;
    else
        id = 1;
}

void Player::keep_jailcard(int id){
    jailcardlist[id] = true;
}

bool Player::willlose(){
    int asset_value = 0;
    vector<Asset*>::iterator p;
    for(p = assetlist.begin(); p != assetlist.end() ; ++p){
        if (!(*p)->get_mortgage_status()){
            asset_value+= (*p)->get_mortgage_value();
            Property* property = dynamic_cast<Property*>(*p);
            if (property!= nullptr){
                asset_value+= property->get_house()*property->get_housecost()/2;
                asset_value+= property->get_hotel()*property->get_housecost()/2;
            }
        }
    }
    losed = true;
    return (asset_value+money+(jailcardlist[0]+jailcardlist[1])*50 < 0 )? true: false;
}

bool Player::islosed(){
    return losed;
}

void Player::bankruptcy(){
    vector<Asset*>::iterator p;
    for(p = assetlist.begin(); p != assetlist.end() ; ++p){
        if (!(*p)->get_mortgage_status()){
            (*p)->set_mortgage();
            Property* property = dynamic_cast<Property*>(*p);
            if (property!= nullptr){
                (*p)->set_mortgage();
            }
        }
    }
    money+= (jailcardlist[0]+jailcardlist[1])*50;
}

