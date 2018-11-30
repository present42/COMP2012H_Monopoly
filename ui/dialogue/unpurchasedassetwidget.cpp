#include "unpurchasedassetwidget.h"
#include "QDebug"

UnpurchasedAssetWidget::UnpurchasedAssetWidget(QWidget* parent):
    QWidget(parent)
{
    setGeometry(OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH / 2, OFFSET + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH / 2,
                8 * BLOCK_NORMAL_WIDTH, 8 * BLOCK_NORMAL_WIDTH);

    instruction = new QLabel(this);
    instruction->setGeometry(BLOCK_NORMAL_WIDTH * 2, 5,
                             BLOCK_NORMAL_WIDTH * 4, BLOCK_NORMAL_WIDTH);
    instruction->setFont(QFont("Georgia", 16));
    instruction->setText("FOR SALE");
    instruction->setAlignment(Qt::AlignCenter);

    price = new QLabel(this);
    price->setGeometry(BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH + 5,
                             BLOCK_NORMAL_WIDTH * 6, BLOCK_NORMAL_WIDTH);
    price->setFont(QFont("Georgia", 16));
    price->setStyleSheet("QLabel { border: 1.5px solid black }");
    price->setText("$200");
    price->setAlignment(Qt::AlignCenter);

    preview = new QLabel(this);
    preview->setGeometry(BLOCK_NORMAL_WIDTH * 5 / 2 , BLOCK_NORMAL_WIDTH * 2 + 5,
                         BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH * 9 / 2);
    //preview->setStyleSheet("QLabel { border: 1.5px solid black }");
    QPixmap temp(":/res/5.png");
    preview->setPixmap(temp.scaled(preview->width(), preview->height(), Qt::KeepAspectRatio));
    purchase_button = new QPushButton(this);
    purchase_button->setGeometry(BLOCK_NORMAL_WIDTH / 2, BLOCK_NORMAL_WIDTH * 13 / 2 + 10,
                                 BLOCK_NORMAL_WIDTH * 5 / 2, BLOCK_NORMAL_WIDTH);
    purchase_button->setText("BUY");
    purchase_button->setFont(QFont("Georgia", 16));

    auction_button = new QPushButton(this);
    auction_button->setGeometry(4 * BLOCK_NORMAL_WIDTH, BLOCK_NORMAL_WIDTH * 13 / 2 + 10,
                                BLOCK_NORMAL_WIDTH * 3, BLOCK_NORMAL_WIDTH);
    auction_button->setText("AUCTION");
    auction_button->setFont(QFont("Georgia", 16));
}

UnpurchasedAssetWidget::~UnpurchasedAssetWidget() {

}
