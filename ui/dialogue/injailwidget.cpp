#include "injailwidget.h"

InJailWidget::InJailWidget(QWidget* parent):
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH / 2, OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH / 2,
                8 * BLOCK_NORMAL_WIDTH, 8 * BLOCK_NORMAL_WIDTH);

    instruction = new QLabel(this);
    instruction->setGeometry(BLOCK_NORMAL_WIDTH * 2, 5,
                             BLOCK_NORMAL_WIDTH * 4, BLOCK_NORMAL_WIDTH);
    instruction->setFont(QFont("Georgia", 16));
    instruction->setText("IN JAIL");
    instruction->setAlignment(Qt::AlignCenter);

    jail_pic = new QLabel(this);
    jail_pic->setGeometry(BLOCK_NORMAL_WIDTH * 3 / 2 , BLOCK_NORMAL_WIDTH * 2 + 5,
                         BLOCK_NORMAL_WIDTH * 5, BLOCK_NORMAL_WIDTH * 4);
    //preview->setStyleSheet("QLabel { border: 1.5px solid black }");
    QPixmap temp(":/res/in_jail.png");
    jail_pic->setPixmap(temp.scaled(jail_pic->width(), jail_pic->height(), Qt::KeepAspectRatio));

    pay_button = new QPushButton(this);
    pay_button->setGeometry(BLOCK_NORMAL_WIDTH / 2, BLOCK_NORMAL_WIDTH * 13 / 2 + 10,
                                 BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH);
    pay_button->setText("POST BAIL\n$50");
    pay_button->setFont(QFont("Georgia", 16));

    use_card = new QPushButton(this);
    use_card->setGeometry(BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH * 13 / 2 + 10,
                                BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH);
    use_card->setText("USE CARD");
    use_card->setFont(QFont("Georgia", 16));

    roll_dice = new QPushButton(this);
    roll_dice->setGeometry(BLOCK_NORMAL_WIDTH * 11 / 2, BLOCK_NORMAL_WIDTH * 13 / 2 + 10,
                                BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH);
    roll_dice->setText("ROLL FOR\nDOUBLE");
    roll_dice->setFont(QFont("Georgia", 16));
}

InJailWidget::~InJailWidget() {
    if(instruction) delete instruction;
    if(jail_pic) delete jail_pic;
    if(pay_button) delete pay_button;
    if(use_card) delete use_card;
    if(roll_dice) delete roll_dice;
}

QPushButton* InJailWidget::getPayButton() {
    return pay_button;
}

QPushButton* InJailWidget::getUseCardButton() {
    return use_card;
}

QPushButton* InJailWidget::getRollDiceButton() {
    return roll_dice;
}

void InJailWidget::handlePayButtonClicked() {
    hide();
    emit injail_choose(0);
}

void InJailWidget::handleUseCardClicked() {
    hide();
    emit injail_choose(1);
}

void InJailWidget::handleRollDiceClicked(){
    hide();
    emit injail_choose(2);
}
