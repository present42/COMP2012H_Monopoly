#ifndef SERVER_H
#define SERVER_H

#include "player.h"
#include "property.h"
#include "utility.h"
#include "railroad.h"
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

    void trigger_event(int dice_num);
    void end_turn();
    void next_player();

    GameWindow* get_game_window();
    void startGUI();
private:
    // for testing one player
    Player* players[4];
    Block* block[40];
    int num_player;
    Player* current_player;
    int  double_count;
    int status;

    //GUI
    //If the server-client program is to be implemented,
    //this part should be removed
    GameWindow* game_window;


signals:
    void init_player(int id);
    void emit_status(int status);
    void emit_player(int index);
    void emit_dice(int first, int second);
    void emit_buy_auction();
    void emit_normal();
    void emit_nomoney();
    void emit_next();


};

#endif // SERVER_H
