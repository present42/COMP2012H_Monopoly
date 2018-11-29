#ifndef TOKENUI_H
#define TOKENUI_H

#include <QLabel>
#include "abstractblockui.h"

class TokenUI : public QLabel
{
public:
    TokenUI(QWidget* parent = nullptr, QString type = "cat", AbstractBlockUI* (*blocks)[40] = nullptr);
    void move(int position);

private:
    const static int START_X = 25;
    const static int START_Y = 25;
    AbstractBlockUI* (*blocks)[40];

};

#endif // TOKENUI_H
