#include "owemoneywidget.h"

OweMoneyWidget::OweMoneyWidget(QWidget* parent) :
    QWidget (parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 3 * BLOCK_NORMAL_WIDTH,
                7 * BLOCK_NORMAL_WIDTH, 4 * BLOCK_NORMAL_WIDTH);
    id_label = new QLabel(this);
    id_label->setGeometry(BLOCK_NORMAL_WIDTH, 5, BLOCK_NORMAL_WIDTH * 6, BLOCK_NORMAL_WIDTH * 2);
    id_label->setText("You owe more money that you\ncan pay. Raise more money or\ndeclare bankruptcy");
    id_label->setFont(QFont("Georgia", 10));
    id_label->setAlignment(Qt::AlignLeft);
    id_label->setWordWrap(true);

    declare_bankrupt_button = new QPushButton(this);
    declare_bankrupt_button->setGeometry(2 * BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH * 2 + 5, BLOCK_NORMAL_WIDTH * 9 / 2, BLOCK_NORMAL_WIDTH / 2);
    declare_bankrupt_button->setText("DECLARE BANKRUPTCY");
    declare_bankrupt_button->setFont(QFont("Georgia", 16));

    connect(declare_bankrupt_button, &QPushButton::clicked, this, &OweMoneyWidget::handleButtonClicked);
}

OweMoneyWidget::~OweMoneyWidget() {
    if(id_label) delete id_label;
    if(declare_bankrupt_button) delete declare_bankrupt_button;
}

void OweMoneyWidget::handleButtonClicked() {
    emit declare_bankrupt_button_clicked();
}
