#include "tokenui.h"

TokenUI::TokenUI(QWidget* parent, QString type, AbstractBlockUI* (*blocks)[40]):
    QLabel(parent),
    blocks(blocks)
{
    show();
    setGeometry(160, 35, 90, 90);
    QString url = ":/res/token_" + type;
    QPixmap pixmap(url);
    setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}

void TokenUI::move(int position) {
    setGeometry((*blocks)[position]->token_pos_x(), (*blocks)[position]->token_pos_y(), 90, 90);
}
