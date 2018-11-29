#ifndef NORMALBLOCKWITHLABELUI_H
#define NORMALBLOCKWITHLABELUI_H

#include "normalblockui.h"
#include <QLabel>

class NormalBlockWithLabelUI : public NormalBlockUI
{
public:
    NormalBlockWithLabelUI(QWidget* parent, int position = 0);
    void render() override;

private:
    QLabel* build_zone;
};

#endif // NORMALBLOCKWITHLABELUI_H
