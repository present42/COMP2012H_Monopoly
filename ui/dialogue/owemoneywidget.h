#ifndef OWEMONEYWIDGET_H
#define OWEMONEYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class OweMoneyWidget : public QWidget
{
    Q_OBJECT
public:
    OweMoneyWidget(QWidget* parent = nullptr);
    ~OweMoneyWidget();

private:
    QPushButton* declare_bankrupt_button;
    QLabel* id_label;
    QLabel* explanation;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;
signals:
    void declare_bankrupt_button_clicked();
};

#endif // OWEMONEYWIDGET_H
