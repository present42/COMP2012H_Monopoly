#include "normalblockui.h"

NormalBlockUI::NormalBlockUI(QWidget* parent, int position):
    AbstractBlockUI (parent, position)
{

}

void NormalBlockUI::render() {
    int x = position % 10;
    QPixmap pixmap(":/res/" + QString::number(position) + ".png");
    switch(position / 10) {
        case 0:
            setGeometry(QRect(OFFSET_X + BLOCK_HEIGHT + (9 - x) * BLOCK_NORMAL_WIDTH, OFFSET_Y + BLOCK_HEIGHT + (9 * BLOCK_NORMAL_WIDTH), BLOCK_NORMAL_WIDTH, BLOCK_HEIGHT));
            setIcon(pixmap.scaled(BLOCK_NORMAL_WIDTH - 4, BLOCK_HEIGHT - 4, Qt::KeepAspectRatio));
            break;
        case 1:
            setGeometry(QRect(OFFSET_X, OFFSET_Y + BLOCK_HEIGHT + (9 - x) * BLOCK_NORMAL_WIDTH, BLOCK_HEIGHT, BLOCK_NORMAL_WIDTH));
            setIcon(pixmap.scaled(BLOCK_HEIGHT - 4, BLOCK_NORMAL_WIDTH - 4, Qt::KeepAspectRatio));
            break;
        case 2:
            setGeometry(QRect(OFFSET_X + BLOCK_HEIGHT + ((x - 1) * BLOCK_NORMAL_WIDTH), OFFSET_Y, BLOCK_NORMAL_WIDTH, BLOCK_HEIGHT));
            setIcon(pixmap.scaled(BLOCK_NORMAL_WIDTH - 4, BLOCK_HEIGHT - 4, Qt::KeepAspectRatio));
            break;
        case 3:
            setGeometry(QRect(OFFSET_X + BLOCK_HEIGHT + (9 * BLOCK_NORMAL_WIDTH), OFFSET_Y + BLOCK_HEIGHT + ((x - 1) * BLOCK_NORMAL_WIDTH), BLOCK_HEIGHT, BLOCK_NORMAL_WIDTH));
            setIcon(pixmap.scaled(BLOCK_HEIGHT - 4, BLOCK_NORMAL_WIDTH - 4, Qt::KeepAspectRatio));
            break;
    }

    setIconSize(pixmap.rect().size() - QSize(4, 4));

    setVisible(true);
    setFlat(true);
    setAutoFillBackground(true);

    setStyle("border-color", "black");
    setStyle("background-color", "rgb(210, 234, 212)");
    setStyle("border-width", "2px");
    setStyle("border-style", "solid");
    applyStyle();
}

int NormalBlockUI::token_pos_x() {
    switch(position / 10) {
        case 1:
        case 3:
            return x() + 35;
        default:
            return x();
    }
}

int NormalBlockUI::token_pos_y() {
    switch(position / 10) {
        case 0:
            return y() + 35;
        default:
            return y();
    }
}
