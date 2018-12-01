#ifndef INJAILWIDGET_H
#define INJAILWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class InJailWidget : public QWidget
{
    Q_OBJECT
public:
    InJailWidget(QWidget* parent = nullptr);
    ~InJailWidget();

    QPushButton* getPayButton();
    QPushButton* getUseCardButton();
    QPushButton* getRollDiceButton();

private:
    QLabel* instruction;
    QPushButton* pay_button;
    QPushButton* use_card;
    QPushButton* roll_dice;

    QLabel* jail_pic;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

signals:
    void injail_choose(int choice);

};

#endif // INJAILWIDGET_H
