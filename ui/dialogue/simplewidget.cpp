#include "simplewidget.h"

SimpleWidget::SimpleWidget(QWidget* parent) :
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 2 * BLOCK_NORMAL_WIDTH,
                7 * BLOCK_NORMAL_WIDTH, 5 * BLOCK_NORMAL_WIDTH);

    explanation = new QLabel(this);
    explanation->setGeometry(BLOCK_NORMAL_WIDTH / 2, BLOCK_NORMAL_WIDTH / 2 + 5,
                             BLOCK_NORMAL_WIDTH * 6, BLOCK_NORMAL_WIDTH * 3);
    explanation->setFont(QFont("Georgia", 16));
    explanation->setStyleSheet("QLabel { border: 1.5px solid black }");
    explanation->setText("{INSTRUCTION TO BE HERE}");
    explanation->setAlignment(Qt::AlignCenter);
    explanation->setWordWrap(true);

    ok_button = new QPushButton(this);
    ok_button->setGeometry(BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH * 4 + 10,
                                 BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH / 2);
    ok_button->setText("OK");
    ok_button->setFont(QFont("Georgia", 16));

    connect(ok_button, &QPushButton::clicked, this, &SimpleWidget::ok_button_clicked_handler);
}

SimpleWidget::~SimpleWidget() {
    if(explanation) delete explanation;
    if(ok_button) delete ok_button;
}

void SimpleWidget::setExplanation(QString explanation) {
    this->explanation->setText(explanation);
}

void SimpleWidget::ok_button_clicked_handler() {
    hide();
    emit ok_button_clicked(type);
}
