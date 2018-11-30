#ifndef ROLLDICEWIDGET_H
#define ROLLDICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <src/player.h>

class RollDiceWidget : public QWidget
{
    Q_OBJECT
public:
    RollDiceWidget(QWidget* parent = nullptr, Player* player = nullptr);
    ~RollDiceWidget();
    void updatePlayer(int player);


private:
    QPushButton* roll_button;
    QLabel* id_label;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

signals:
    void roll_button_clicked();

private slots:
    void roll_button_click_handler();
};

#endif // ROLLDICEWIDGET_H
