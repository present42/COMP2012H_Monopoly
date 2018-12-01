#include "payrentwidget.h"

PayRentWidget::PayRentWidget(QWidget* parent):
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH, OFFSET + BLOCK_HEIGHT + 2 * BLOCK_NORMAL_WIDTH,
                7 * BLOCK_NORMAL_WIDTH, 5 * BLOCK_NORMAL_WIDTH);

    exp_label = new QLabel(this);
    exp_label->setGeometry(BLOCK_NORMAL_WIDTH * 5 / 2, 5, BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH / 2);
    exp_label->setFont(QFont("Georgia", 16));
    exp_label->setAlignment(Qt::AlignCenter);
    exp_label->setText("Pay Rent");

    price_label = new QLabel(this);
    price_label->setGeometry(BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH / 2 + 5,
                             BLOCK_NORMAL_WIDTH * 5, BLOCK_NORMAL_WIDTH / 2);
    price_label->setFont(QFont("Georgia", 16));
    price_label->setStyleSheet("QLabel { border: 1.5px solid black }");
    price_label->setText("$200");
    price_label->setAlignment(Qt::AlignCenter);

    payer = new QLabel(this);
    payer->setGeometry(BLOCK_NORMAL_WIDTH * 1 / 2 , BLOCK_NORMAL_WIDTH * 3 / 2 + 5,
                         BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH * 2);
    payer->setStyleSheet("QLabel { border: 1.5px solid black }");
    //QPixmap temp(":/res/5.png");
    //payer->setPixmap(temp.scaled(payer->width(), payer->height(), Qt::KeepAspectRatio));

    arrow_sign = new QLabel(this);
    arrow_sign->setGeometry(BLOCK_NORMAL_WIDTH * 3 , BLOCK_NORMAL_WIDTH * 2 + 5,
                         BLOCK_NORMAL_WIDTH * 1, BLOCK_NORMAL_WIDTH * 1);
    arrow_sign->setFont(QFont("Georgia", 50));
    arrow_sign->setText("🡆");
    arrow_sign->setAlignment(Qt::AlignCenter);

    receiver = new QLabel(this);
    receiver->setGeometry(BLOCK_NORMAL_WIDTH * 9 / 2 , BLOCK_NORMAL_WIDTH * 3 / 2 + 5,
                         BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH * 2);
    receiver->setStyleSheet("QLabel { border: 1.5px solid black }");
    //QPixmap temp(":/res/5.png");
    //receiver->setPixmap(temp.scaled(receiver->width(), receiver->height(), Qt::KeepAspectRatio));

    ok_button = new QPushButton(this);
    ok_button->setGeometry(BLOCK_NORMAL_WIDTH * 2, BLOCK_NORMAL_WIDTH * 4 + 10,
                                 BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH / 2);
    ok_button->setText("OK");
    ok_button->setFont(QFont("Georgia", 16));

    connect(ok_button, &QPushButton::clicked, this, &PayRentWidget::ok_button_clicked_handler);
}

PayRentWidget::~PayRentWidget() {

}

void PayRentWidget::setRent(int rent) {
    price_label->setText(QString("$") + QString::number(rent));
}

void PayRentWidget::setPayer(TokenUI* token) {
    QPixmap temp(":/res/token_" + token->getTokenString() + ".png");
    payer->setPixmap(temp.scaled(payer->width(), payer->height(), Qt::KeepAspectRatio));
}

void PayRentWidget::setReceiver(TokenUI* token) {
    QPixmap temp(":/res/token_" + token->getTokenString() + ".png");
    receiver->setPixmap(temp.scaled(receiver->width(), receiver->height(), Qt::KeepAspectRatio));
}

void PayRentWidget::ok_button_clicked_handler() {
    hide();
    emit ok_button_clicked();
}
