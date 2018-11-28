#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

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
    //QLabel* tokens[4];
    //AbstractBlock* test[4][8];
    //SpecialBlock* block[4];
    //HoverDialogue* hoverDialog;
    void closeEvent(QCloseEvent *event);
private slots:
    //void processHoverEnterWithInput(int x, int y);
    //void processHoverLeaveWithInput(int x, int y);

signals:
    void closed();
};

#endif // GAMEWINDOW_H
