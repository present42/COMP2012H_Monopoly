#ifndef SERVER_H
#define SERVER_H

#include "player.h"
#include "token.h"
#include "property.h"
#include "utility.h"
#include "railroad.h"
#include "gotojail.h"
#include "selectcard.h"
#include "card.h"
#include "charge.h"
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
    void do_next_job();

    void trigger_event(int dice_num);
    void end_turn();

    void bankruptcy();

    GameWindow* get_game_window();
    void startGUI();
private:
    vector<Player*> players;
    Block* block[40];
    SelectCard* chance_block;
    SelectCard* community_block;
    Player* current_player;

    int  double_count;
    int prev_status;
    int status;

    void initboard();

    //GUI
    GameWindow* gamewindow;

public slots:
    void next_player();
    void drawn_after();
    void purchaseProperty();
    void checkdouble();
    void in_jail_action(int num);
<<<<<<< HEAD
    void build_handler(int pos);
    void mortgage_handler(int pos);
    void demortgage_handler(int pos);

=======
    void buildSomething();
    void handleSimpleWidgetOKButton(int type);
>>>>>>> f930a1bb6959bbb873760cc582265d283e44ab37
signals:
    void pay_bank(int money);
    void pay_rent(int ownerid, int rent);
    void card_drawn(bool set, QString instruction);
    void asset_bought(int pos);

    void init_player(int id);
    void status_changed(int status);
    void player_moved(int id);
    void dice_thrown(int first, int second);

    //void normal();
    //void nomoney();
    void next(int id);


    void pass_asset_price(int price);

};

#endif // SERVER_H
