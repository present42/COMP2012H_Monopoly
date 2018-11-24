#include <cstdlib>
#include <ctime>
#include "server.h"
#include "QtDebug"
using namespace std;

Server::Server():
  current_player(Player(1,Token::Test1)),
  double_count(0)
{
    srand(time(0));
}

int Server::roll_dice(){
    int first = rand()%6+1;
    int second = rand()%6+1;
    bool doubles = (first == second);
    double_count += doubles?1:0;
    //animation pop up ....
    return first+second;
}

void Server::game_flow(){
    double_count = 0;
    if (current_player.is_injail())
    {

    }else{
        do{
            int steps = roll_dice();
            if (double_count ==3){
                // go to jail
                //move_token
                current_player.movebyposition(10);
                current_player.stayin_jail();
            }else{
                //normal
                move_token(steps);
                trigger_event();
            }
        } while(double_count>0);
    }
    next_player();
}

void Server::move_token(int steps){
    current_player.movebysteps(steps);
}

void Server::trigger_event(){
    if(current_player.is_passed_GO()){
        //pop up + money
        current_player.set_passed_GO(false);
    }

}

void Server::next_player(){

}



