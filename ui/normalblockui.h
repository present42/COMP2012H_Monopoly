#ifndef NORMALBLOCKUI_H
#define NORMALBLOCKUI_H

#include "abstractblockui.h"

class NormalBlockUI : public AbstractBlockUI
{
public:
    NormalBlockUI(QWidget* parent = nullptr, int position = 0);
    virtual void render() override;

    virtual int token_pos_x() override;
    virtual int token_pos_y() override;
};

#endif // NORMALBLOCKUI_H
