#include "player.h"

Player::Player(int id, Token token):
  id(id),
  asset(0),
  position(0),
  passed_GO(false),
  token(token)
{

}

void Player::movebysteps(int steps){
    passed_GO = false;
    position += steps;
    if (position < 0){
        position += 40;
    }else if (position > 39){
        passed_GO = true;
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

bool Player::is_passed_GO() const{
    return passed_GO;
}

bool Player::is_injail() const{
    return (jail_turn== -1)? false: true;
}

void Player::set_passed_GO(bool passed) {
    passed_GO = passed;
}

void Player::out_jail(){
    jail_turn = -1;
}

void Player::stayin_jail(){
    jail_turn += 1;
}
