#include <cstdlib>
#include <ctime>
#include "server.h"
#include <QtDebug>
#include "ui/rolldicewidget.h"
#include "token.h"

using namespace std;

Server::Server():
  current_player(nullptr),
  double_count(0)
{
    srand(time(0));
}

Server::~Server() {

}

void Server::add_player(Player* new_player) {
    if(num_player < 4) {
        players[num_player++] = new_player;
        emit init_player(new_player->get_playerid());
    } else return;
}

/*
 * [Suggestion on Game Flow]
 * This function is called when the clients agree to start (all click the button)
 * Before this function is called, all participating players should be initiated
 *
 * <<Status Indicator>>
 * 0.5 : jail
 * 1 : Before rolling the dice
 * 2 : After rolling the dice. Current player has to choose something
 * -2a : buy or auction
 * -2b : follow instruction (pay rent, pay .. to bank, receive money from bank, move to somewhere)
 * -2c : not enough money
 * 3 : Before ending his turn
 *
 * #1 : build
 * #2 : mortgage
 * #3 : unmortgage
 * #4 : trade
 */
void Server::status_change(int status){
    this->status = status;
    //After changing the status, please emit the signal (status change)
}


void Server::start() {
    //Randomly select the current player() [Server -> Client GUI]
    current_player = players[rand() % 4];
    //Wait a signal to roll the dice from Client GUI
    //status_change(1);
}

//Define it as a slot (throw the dice only if the client sends the signal to do so)
void Server::roll_dice() {

    int first = rand() % 6 + 1;
    int second = rand() % 6 + 1;

    bool doubles = (first == second);
    if(doubles)
        ++double_count;
    else
        double_count = 0;

    //emit signal to GUI
    qDebug() << first << " and " << second;
/*
    //special action if player is in jail
    if (current_player->is_injail()) {
        if(doubles) {
            //If you get double, you're out of jail!
            current_player->out_jail();
        } else if(current_player->get_jail_turn() == 3) {
            //If you don't get double, but it's three times for you to be in jail
            //You pay fine $50 and out of jail

            //TODO - function call for paying $50 to the bank
            current_player->out_jail();
        }
    } else if(double_count == 3) {
        current_player->movebyposition(10);
        current_player->stayin_jail();
    }

    if(!current_player->is_injail()) {
        move(first + second);
    } else {
        current_player->stayin_jail();
        //Set status to the last status
    } */
}

void Server::move(int dice_sum){
    current_player->movebysteps(dice_sum);
    //trigger_event();

    if(double_count > 0) {
        //Set status to 1 (Waiting for the current player to throw the dice)
    } else {
        //Set status to the last status
    }
}

void Server::movebysteps(int steps){
    current_player->movebysteps(steps);
}

void Server::movebyposition(int position){
    current_player->movebyposition(position);
}

void Server::trigger_event(){
    if(current_player->is_passed_GO()){
        //pop up + money
        current_player->set_passed_GO(false);
    }

    //trigger block-related event
}

/*
 * Here, we should include the logic to check winning condition
 * in order to decide whether to continue game or not
 */
void Server::next_player(){
    int index = (current_player->get_playerid() + 1) % 4;
    current_player = players[index];
    double_count = 0;
}


