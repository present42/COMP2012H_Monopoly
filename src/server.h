#ifndef SERVER_H
#define SERVER_H

#include "player.h"
class Server{
    private:
    // for testing one player
    Player current_player;
    int  double_count;
    public:
    //recieve the array of player
    Server();
    void game_flow();
    int roll_dice();
    void move_token(int steps);
    void trigger_event();
    void next_player();
};

#endif // SERVER_H
