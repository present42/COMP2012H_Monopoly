#ifndef SPECIALBLOCKUI_H
#define SPECIALBLOCKUI_H

#include "abstractblockui.h"

class SpecialBlockUI : public AbstractBlockUI
{
public:
    SpecialBlockUI(QWidget* parent = nullptr, int position = 0);
    virtual void render() override;
    virtual int token_pos_x() override;
    virtual int token_pos_y() override;
};

#endif // SPECIALBLOCKUI_H
