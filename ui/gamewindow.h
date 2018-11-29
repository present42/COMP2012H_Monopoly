#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "abstractblockui.h"
#include "tokenui.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    enum class Token { HAT, BOOT, SHIP, CAR, DOG, CAT };

    explicit GameWindow(QWidget *parent = nullptr);
    virtual ~GameWindow();
    void setDice(int dice1, int dice2);
    void initToken(int player, Token token_type);

private:
    Ui::GameWindow *ui;
    QFont dice;
    TokenUI* tokens[4];

    AbstractBlockUI* block_ui[40];
    //HoverDialogue* hoverDialog;
    void closeEvent(QCloseEvent *event);
private slots:
    //void processHoverEnterWithInput(int x, int y);
    //void processHoverLeaveWithInput(int x, int y);

signals:
    void closed();
};

#endif // GAMEWINDOW_H
