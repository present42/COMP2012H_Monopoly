#include "tokenui.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
TokenUI::TokenUI(QWidget* parent, Token type, AbstractBlockUI* (*blocks)[40]):
    QLabel(parent),
    blocks(blocks),
    type(type)
{
    show();
    setGeometry(QRect((*blocks)[0]->token_pos_x(), (*blocks)[0]->token_pos_y(), 90, 90));
    QString url = ":/res/token_" + getTokenString();
    QPixmap pixmap(url);
    setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}

void TokenUI::move(int position) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    int temp_stop = current_position;
    for(int i = current_position + 1; i != ((position + 1) % 40); (++i) %= 40) {
        if(i % 10 == 0 || i == position) {
            if(i == current_position) continue;
            QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
            animation->setDuration((i - temp_stop) * 200);
            animation->setStartValue(QRect((*blocks)[temp_stop]->token_pos_x(), (*blocks)[temp_stop]->token_pos_y(), 90, 90));
            animation->setEndValue(QRect((*blocks)[i]->token_pos_x(), (*blocks)[i]->token_pos_y(), 90, 90));
            group->addAnimation(animation);
            qDebug() << temp_stop << "=>" << i;
            temp_stop = i;
        }
        //skip if i is not divided by 10
    }
    current_position = position;
    group->start(QAbstractAnimation::DeleteWhenStopped);
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

int TokenUI::getPosition() const {
    return current_position;
}
