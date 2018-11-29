#include "normalblockwithlabelui.h"

NormalBlockWithLabelUI::NormalBlockWithLabelUI(QWidget* parent, int position):
    NormalBlockUI (parent, position)
{

}

void NormalBlockWithLabelUI::render() {
    this->NormalBlockUI::render();

    build_zone = new QLabel(this);
    int color = (position / 10) * 2 + ((position % 10) > 5);
    switch(color) {
        case 0:
            build_zone->setGeometry(1, 0, BLOCK_NORMAL_WIDTH - 2, BLOCK_HEIGHT / 4 - 2);
            build_zone->setStyleSheet("QLabel { background-color: #955436; border-width: 2px; }");
            break;
        case 1:
            build_zone->setGeometry(1, 0, BLOCK_NORMAL_WIDTH - 2, BLOCK_HEIGHT / 4 - 2);
            build_zone->setStyleSheet("QLabel { background-color: #ade1fa; border-width: 2px; }");
            break;
        case 2:
            build_zone->setGeometry(BLOCK_HEIGHT * 3 / 4, 0, BLOCK_HEIGHT / 4 - 2, BLOCK_HEIGHT);
            build_zone->setStyleSheet("QLabel { background-color: #d94999; border-width: 2px; }");
            break;
        case 3:
            build_zone->setGeometry(BLOCK_HEIGHT * 3 / 4, 0, BLOCK_HEIGHT / 4 - 2, BLOCK_HEIGHT);
            build_zone->setStyleSheet("QLabel { background-color: #f89734; border-width: 2px; }");
            break;
        case 4:
            build_zone->setGeometry(0, BLOCK_HEIGHT * 3 / 4, BLOCK_NORMAL_WIDTH, BLOCK_HEIGHT / 4);
            build_zone->setStyleSheet("QLabel { background-color: #ee3338; border-width: 2px; }");
            break;
        case 5:
            build_zone->setGeometry(0, BLOCK_HEIGHT * 3 / 4, BLOCK_NORMAL_WIDTH, BLOCK_HEIGHT / 4);
            build_zone->setStyleSheet("QLabel { background-color: #fff213; border-width: 2px; }");
            break;
        case 6:
            build_zone->setGeometry(0, 0, BLOCK_HEIGHT / 4, BLOCK_HEIGHT);
            build_zone->setStyleSheet("QLabel { background-color: #00a85a; border-width: 2px;}");
            break;
        case 7:
            build_zone->setGeometry(0, 0, BLOCK_HEIGHT / 4, BLOCK_HEIGHT);
            build_zone->setStyleSheet("QLabel { background-color: #0077be; border-width: 2px;}");
            break;
        default:
            break;
    }
}

