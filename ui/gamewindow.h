#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "abstractblockui.h"
#include "tokenui.h"
#include "dialogue/rolldicewidget.h"
#include "dialogue/unpurchasedassetwidget.h"
#include "dialogue/endturnwidget.h"
#include "dialogue/owemoneywidget.h"
#include "dialogue/injailwidget.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT
public:

    explicit GameWindow(QWidget *parent = nullptr);
    virtual ~GameWindow();
    void setDice(int dice1, int dice2);
    void initToken(int player, TokenUI::Token token_type);
    RollDiceWidget* getRollDiceWidget();

private:
    Ui::GameWindow *ui;
    int game_status;

    QFont dice_font;

    TokenUI* tokens[4];
    int current_token;
    TokenUI::Token token_list[6];
    int token_num;

    AbstractBlockUI* block_ui[40];

    RollDiceWidget* roll_dice_widget;
    UnpurchasedAssetWidget* unpurchased_asset_widget;
    EndTurnWidget* end_turn_widget;
    OweMoneyWidget* owe_money_widget;
    InJailWidget* in_jail_widget;

    QLabel* dice[2];

    QWidget* player_property_list_widget[4];

    void initTabWidget(int new_tab);

    //HoverDialogue* hoverDialog;
    void initDice();
    void relocateDice();

    void initRollDiceWidget();
    void initUnpurchasedAssetWidget();
    void initEndTurnWidget();
    void initOweMoneyWidget();
    void initInJailWidget();

    void closeEvent(QCloseEvent *event);
    void hideAllDialogues();

public slots:
    void end_turn_button_clicked();

    void init_player(int id);
    void handleStatusChange(int status);
    void setCurrentPlayer(int index);
    void showDiceNumber(int first, int second);
    void moveToken(int position);
    //void processHoverEnterWithInput(int x, int y);
    //void processHoverLeaveWithInput(int x, int y);

signals:
    void closed();
    void turn_finished();
};

#endif // GAMEWINDOW_H
