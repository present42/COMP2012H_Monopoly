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
#include "dialogue/payrentwidget.h"
#include "dialogue/cardwidget.h"
#include "dialogue/simplewidget.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT
public:

    explicit GameWindow( QWidget *parent = nullptr, Block* board[40] = nullptr);
    virtual ~GameWindow();
    void setDice(int dice1, int dice2);
    void initToken(int player, TokenUI::Token token_type);
    RollDiceWidget* getRollDiceWidget();
    UnpurchasedAssetWidget* getUnpurchasedAssetWidget();
    PayRentWidget* getPayRentWidget();
    CardWidget* getCardWidget();
    SimpleWidget* getSimpleWidget();
    InJailWidget* getInJailWidget();
    OweMoneyWidget* getOweMoneyWidget();

    QPushButton* getBuildButton();
    QPushButton* getMortgageButton();
    QPushButton* getUnmortgageButton();
    QPushButton* getSellButton();

    void init_player(int id);
    void refresh(vector<Player*> players, Block* (*block)[40]);
    void updateInJailDialogue(bool affordable, bool have_card);
    void setWarningMesseage(QString);
    void hideWarningMessage();
private:
    Ui::GameWindow *ui;
    Block** board;
    int game_status;

    /*
     * Those data members are soly for displaying.
     */
    int money[4];

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
    PayRentWidget* pay_rent_widget;
    CardWidget* card_widget;
    SimpleWidget* simple_widget;

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
    void initPayRentWidget();
    void initCardWidget();
    void initSimpleWidget();

    void closeEvent(QCloseEvent *event);
    void hideAllDialogues();

    void updateMoney(int player, int amount, bool bankrupt = false);
    void updateAssetInfo(int player, int position, int value);


    QString getBorderStyle(int position);

public slots:
    void end_turn_button_clicked();

    void handleStatusChange(int status);

    void getAssetPrice(int price);
    void getRentInfo(int receiver, int amount);
    void buyAsset(int position);

    void payToBank(int amount);
    void payToOtherPlayer(int receiver, int amount);
    void payToOthers(int amount);

    void receiveFromBank(int amount);
    void receiveFromOthers(int amount);

    void setCurrentPlayer(int index);
    void showDiceNumber(int first, int second);
    void moveToken(int position);
    void hideToken(int id);

    void setCardInstruction(bool isChanceCard, QString instruction);
    void handleButtonClicked(int position);
    //void processHoverEnterWithInput(int x, int y);
    //void processHoverLeaveWithInput(int x, int y);

signals:
//    void click_build();
    void closed();
    void turn_finished();
    void block_clicked(int position);
};

#endif // GAMEWINDOW_H
