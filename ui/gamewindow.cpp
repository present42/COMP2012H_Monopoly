#include "ui/gamewindow.h"
#include "ui_gamewindow.h"

#include <QFont>
#include <QFontDatabase>
#include "blockuifactory.h"
#include "specialblockui.h"
#include "normalblockui.h"
#include "normalblockwithlabelui.h"

GameWindow::GameWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
    //dice(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/font/Dice.ttf")).at(0), 50))
{
    ui->setupUi(this);

    for(int i = 0; i < 40; i++) {
        block_ui[i] = BlockUIFactory::createBlock(this, i);
        block_ui[i]->render();
    }

    tokens[0] = new TokenUI(this, "cat", &block_ui);
    this->show();
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::closeEvent(QCloseEvent *event) {
    emit closed();
}
