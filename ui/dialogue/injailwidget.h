#ifndef INJAILWIDGET_H
#define INJAILWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class InJailWidget : public QWidget
{
    Q_OBJECT
public:
    InJailWidget(QWidget* parent = nullptr);
    ~InJailWidget();

private:
    QPushButton* pay_button;
    QPushButton* use_card;
    QPushButton* roll_dice;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

signals:

};

#endif // INJAILWIDGET_H
