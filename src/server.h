#ifndef SERVER_H
#define SERVER_H

#include "player.h"
#include "ui/gamewindow.h"

class Server{
public:
    Server();
    void game_flow();
    int roll_dice();
    void movebysteps(int steps);
    void movebyposition(int positions);
    void trigger_event();
    void injail_action();
    void next_player();

private:
    // for testing one player
    Player* playerlist[4];
    Player* current_player;
    int  double_count;

    //GUI
    //If the server-client program is to be implemented,
    //this part should be removed
    GameWindow* game_window;
};

#endif // SERVER_H
