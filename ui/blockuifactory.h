#ifndef BLOCKUIFACTORY_H
#define BLOCKUIFACTORY_H

#include "abstractblockui.h"
#include "specialblockui.h"
#include "normalblockui.h"
#include "normalblockwithlabelui.h"

class BlockUIFactory
{
public:
    static AbstractBlockUI* createBlock(QWidget* parent, int position) {
        if(position % 10 == 0) {
            return new SpecialBlockUI(parent, position);
        } else if(position == 4 || position == 33 || (position % 10 == 2 && position < 30)
                  || position % 10 == 5 || position == 36 || (position % 10 == 7 && position < 20) ||
                  (position % 10 == 8 && position > 20)) {
            return new NormalBlockUI(parent, position);
        } else {
            return new NormalBlockWithLabelUI(parent, position);
        }
    }
};

#endif // BLOCKUIFACTORY_H
