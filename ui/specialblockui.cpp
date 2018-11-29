#include "specialblockui.h"

SpecialBlockUI::SpecialBlockUI(QWidget* parent, int position):
    AbstractBlockUI (parent, position)
{

}

void SpecialBlockUI::render() {
    setVisible(true);
    setFlat(true);
    setStyle("border-color", "black");
    setStyle("background-color", "rgb(210, 234, 212)");
    QString url;
    switch(position / 10) {
        case 0:
            setGeometry(OFFSET_X + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH * 9, OFFSET_Y + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH * 9, BLOCK_HEIGHT, BLOCK_HEIGHT);
            url = ":/res/go.png";
            break;
        case 1:
            setGeometry(OFFSET_X, OFFSET_Y + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH * 9, BLOCK_HEIGHT, BLOCK_HEIGHT);
            url = ":/res/jail.png";
            break;
        case 2:
            setGeometry(OFFSET_X, OFFSET_Y, BLOCK_HEIGHT, BLOCK_HEIGHT);
            url = ":/res/parking.png";
            break;
        case 3:
            setGeometry(OFFSET_X + BLOCK_HEIGHT + BLOCK_NORMAL_WIDTH * 9, OFFSET_Y, BLOCK_HEIGHT, BLOCK_HEIGHT);
            url = ":/res/police.png";
            break;
    }
    QPixmap pixmap(url);
    setIcon(pixmap.scaled(BLOCK_HEIGHT - 4, BLOCK_HEIGHT - 4, Qt::KeepAspectRatio));
    setIconSize(pixmap.rect().size() - QSize(4, 4));
    setStyle("border-width", "2px");
    setStyle("border-style", "solid");
    applyStyle();
}

int SpecialBlockUI::token_pos_x() {
    switch(position / 10) {
        case 1:
        case 2:
            return x() + 15;
        default:
            return x() + 35;
    }
}

int SpecialBlockUI::token_pos_y() {
    switch(position / 10) {
        case 0:
        case 1:
            return y() + 35;
        default:
            return y() + 15;
    }
}

