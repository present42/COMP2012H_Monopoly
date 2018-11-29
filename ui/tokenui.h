#ifndef TOKENUI_H
#define TOKENUI_H

#include <QLabel>
#include "abstractblockui.h"
#include "src/token.h"

class TokenUI : public QLabel
{
public:
    TokenUI(QWidget* parent = nullptr, Token type = Token::CAT, AbstractBlockUI* (*blocks)[40] = nullptr);
    void move(int position);

private:
    const static int START_X = 25;
    const static int START_Y = 25;
    AbstractBlockUI* (*blocks)[40];
    Token type;

    QString getTokenString();
};

#endif // TOKENUI_H
