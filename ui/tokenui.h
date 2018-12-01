#ifndef TOKENUI_H
#define TOKENUI_H

#include <QLabel>
#include "abstractblockui.h"

class TokenUI : public QLabel
{
public:
    enum class Token { HAT, BOOT, SHIP, CAR, DOG, CAT };

    TokenUI(QWidget* parent = nullptr, Token type = Token::CAT, AbstractBlockUI* (*blocks)[40] = nullptr);
    void move(int position);
    int getPosition() const;

    QString getTokenString();
private:
    const static int START_X = 25;
    const static int START_Y = 25;
    AbstractBlockUI* (*blocks)[40];
    Token type;
    int current_position = 0;


};

#endif // TOKENUI_H
