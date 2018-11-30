#include "tokenui.h"

TokenUI::TokenUI(QWidget* parent, Token type, AbstractBlockUI* (*blocks)[40]):
    QLabel(parent),
    blocks(blocks),
    type(type)
{
    show();
    setGeometry(160, 35, 90, 90);
    QString url = ":/res/token_" + getTokenString();
    QPixmap pixmap(url);
    setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}

void TokenUI::move(int position) {
    setGeometry((*blocks)[position]->token_pos_x(), (*blocks)[position]->token_pos_y(), 90, 90);
}

QString TokenUI::getTokenString() {
    switch(type) {
        case Token::CAT:
            return "cat";
        case Token::BOOT:
            return "boot";
        case Token::CAR:
            return "car";
        case Token::DOG:
            return "dog";
        case Token::HAT:
            return "hat";
        case Token::SHIP:
            return "ship";
    }
}
