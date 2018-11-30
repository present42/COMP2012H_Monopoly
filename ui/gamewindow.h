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
    QFont dice;
    TokenUI* tokens[4];
    TokenUI* current_token = nullptr;

    AbstractBlockUI* block_ui[40];

    RollDiceWidget* roll_dice_widget;
    UnpurchasedAssetWidget* unpurchased_asset_widget;
    EndTurnWidget* end_turn_widget;
    OweMoneyWidget* owe_money_widget;
    InJailWidget* in_jail_widget;
    //HoverDialogue* hoverDialog;
    void initRollDiceWidget();
    void initUnpurchasedAssetWidget();
    void initEndTurnWidget();
    void initOweMoneyWidget();
    void initInJailWidget();

    void closeEvent(QCloseEvent *event);
    void hideAllDialogues();

public slots:
    void init_player(int id);
    void statusChangeHandler(int status);
    void setCurrentPlayer(int index);
    //void processHoverEnterWithInput(int x, int y);
    //void processHoverLeaveWithInput(int x, int y);

signals:
    void closed();
};

#endif // GAMEWINDOW_H
