#ifndef SERVER_H
#define SERVER_H

#include "player.h"
class Server{
    private:
    // for testing one player
    Player* playerlist[4];
    Player* current_player;
    int  double_count;

    public:
    Server();
    void game_flow();
    int roll_dice();
    void movebysteps(int steps);
    void movebyposition(int positions);
    void trigger_event();
    void injail_action();
    void next_player();
};

#endif // SERVER_H
