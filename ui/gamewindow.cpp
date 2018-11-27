#include "ui/gamewindow.h"
#include "ui_gamewindow.h"

#include <QFont>
#include <QFontDatabase>

GameWindow::GameWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    dice(QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/font/Dice.ttf")).at(0), 50))
{
}

GameWindow::~GameWindow() {

}
