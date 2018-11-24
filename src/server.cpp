#include <cstdlib>
#include <ctime>
#include "server.h"
#include "QtDebug"
using namespace std;

Server::Server():
  current_player( new Player(1,Token::Test1)),
  double_count(0)
{
    srand(time(0));
}

int Server::roll_dice(){
    int first = rand()%6+1;
    int second = rand()%6+1;
    bool doubles = (first == second);
    double_count += doubles?1:0;
    //special for injail player
    if (current_player->is_injail() && doubles){
        current_player->out_jail();
    }
    //animation pop up ....
    return first+second;
}

void Server::game_flow(){
    double_count = 0;
    if (current_player->is_injail())
    {
        // injail
        injail_action();
    }else{
        do{
            int steps = roll_dice();
            if (double_count ==3){
                // go to jail
                //move_token
                current_player->movebyposition(10);
                current_player->stayin_jail();
            }else{
                //normal
                movebysteps(steps);
                trigger_event();
            }
        } while(double_count>0);
    }
    next_player();
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

}
/*
 *  3 actions
 *  connect
 *  pay fine , use card or roll double
 *  note: if roll 3 times, cant roll anymore
 *
 */
void Server::injail_action(){
    //ask for action

    //action for roll
    int steps  = roll_dice();
    if (!current_player->is_injail()){
        current_player->movebysteps(steps);
    }else{
        current_player->stayin_jail();
    }
}

void Server::next_player(){
    int index = (current_player->get_playerid()+1) % 4;
    current_player = playerlist[index];
}



