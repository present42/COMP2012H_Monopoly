#include "cardwidget.h"

CardWidget::CardWidget(QWidget* parent):
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 2 * BLOCK_NORMAL_WIDTH,
                7 * BLOCK_NORMAL_WIDTH, 5 * BLOCK_NORMAL_WIDTH);

    reader = new QLabel(this);
    reader->setGeometry(BLOCK_NORMAL_WIDTH * 4, 5,
                        BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH / 2);
    reader->setFont(QFont("Georgia", 16));
    reader->setAlignment(Qt::AlignCenter);
    reader->setText("Player #");

    instruction = new QLabel(this);
    instruction->setGeometry(BLOCK_NORMAL_WIDTH / 2, BLOCK_NORMAL_WIDTH / 2 + 5,
                             BLOCK_NORMAL_WIDTH * 6, BLOCK_NORMAL_WIDTH * 3);
    instruction->setFont(QFont("Georgia", 16));
    instruction->setStyleSheet("QLabel { border: 1.5px solid black }");
    instruction->setText("COMMUNITY CHEST\n\nGET OUT OF JAIL\nThis card may be kept until needed or traded");
    instruction->setAlignment(Qt::AlignCenter);

    ok_button = new QPushButton(this);
    ok_button->setGeometry(BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH * 4 + 10,
                                 BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH / 2);
    ok_button->setText("OK");
    ok_button->setFont(QFont("Georgia", 16));

    connect(ok_button, &QPushButton::clicked, this, &CardWidget::ok_button_clicked_handler);
}

CardWidget::~CardWidget() {

}

void CardWidget::setInstruction(QString instruction) {
    this->instruction->setText(instruction);
}

void CardWidget::setReader(int id) {
    reader->setText("Player #" + QString::number(id));
}

void CardWidget::ok_button_clicked_handler() {
    hide();
    emit ok_button_clicked();
}
