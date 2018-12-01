#include "rolldicewidget.h"

RollDiceWidget::RollDiceWidget(QWidget* parent, Player* player):
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 3 * BLOCK_NORMAL_WIDTH, 7 * BLOCK_NORMAL_WIDTH, 3 * BLOCK_NORMAL_WIDTH);
    id_label = new QLabel(this);
    id_label->setGeometry(BLOCK_NORMAL_WIDTH * 5 / 2, 5, BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH / 2);
    id_label->setFont(QFont("Georgia", 16));
    id_label->setAlignment(Qt::AlignCenter);

    roll_button = new QPushButton(this);
    roll_button->setGeometry(4 * BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH * 5 / 2, BLOCK_NORMAL_WIDTH / 2);
    roll_button->setText("ROLL DICE");
    roll_button->setFont(QFont("Georgia", 20));
    connect(roll_button, &QPushButton::clicked, this, &RollDiceWidget::roll_button_click_handler);


    if(player != nullptr) {
        id_label->setText(QString::number(player->get_playerid()));
    } else {
        id_label->setText("NO USER");
    }
}

RollDiceWidget::~RollDiceWidget() {
    if(id_label) delete id_label;
    if(roll_button) delete roll_button;
}

void RollDiceWidget::roll_button_click_handler() {
    hide();
    emit roll_button_clicked();
}

void RollDiceWidget::updatePlayer(int player) {
    id_label->setText("Player " + QString::number(player + 1));
}
