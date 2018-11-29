#ifndef SERVER_H
#define SERVER_H

#include "player.h"
#include "ui/gamewindow.h"
#include <QObject>

class Server : public QObject {
    Q_OBJECT
public:
    Server();
    virtual ~Server();
    void start();
    //void add_new_player();

    /* INITINATION */
    void add_player(Player* new_player);

    /* GAME FLOW */
    void roll_dice();
    void move(int dice_sum);
    void status_change(int status);

    void movebysteps(int steps);
    void movebyposition(int positions);
    void trigger_event();
    void end_turn();
    void next_player();

private:
    // for testing one player
    Player* players[4];
    int num_player;

    Player* current_player;
    int  double_count;
    int status;

    //GUI
    //If the server-client program is to be implemented,
    //this part should be removed


signals:
    void init_player(int id);


};

#endif // SERVER_H
