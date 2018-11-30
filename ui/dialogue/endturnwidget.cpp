#include "endturnwidget.h"

EndTurnWidget::EndTurnWidget(QWidget* parent):
    QWidget (parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 3 * BLOCK_NORMAL_WIDTH, 7 * BLOCK_NORMAL_WIDTH, 3 * BLOCK_NORMAL_WIDTH);
    id_label = new QLabel(this);
    id_label->setGeometry(BLOCK_NORMAL_WIDTH * 5 / 2, 5, BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH / 2);
    id_label->setFont(QFont("Georgia", 16));
    id_label->setAlignment(Qt::AlignCenter);
    id_label->setText("Dummy");

    end_turn_button = new QPushButton(this);
    end_turn_button->setGeometry(4 * BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH * 5 / 2, BLOCK_NORMAL_WIDTH / 2);
    end_turn_button->setText("END TURN");
    end_turn_button->setFont(QFont("Georgia", 20));
}

EndTurnWidget::~EndTurnWidget() {
    if(id_label) delete id_label;
    if(end_turn_button) delete end_turn_button;
}
