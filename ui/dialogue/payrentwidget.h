#ifndef PAYRENTWIDGET_H
#define PAYRENTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "ui/tokenui.h"

class PayRentWidget : public QWidget
{
    Q_OBJECT
public:
    PayRentWidget(QWidget* parent = nullptr);
    ~PayRentWidget();

    void setRent(int rent);
    void setPayer(TokenUI* token);
    void setReceiver(TokenUI* token);

private:
    QLabel* exp_label;
    QLabel* price_label;
    QLabel* payer;
    QLabel* arrow_sign;
    QLabel* receiver;

    QPushButton* ok_button;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

private slots:
    void ok_button_clicked_handler();

signals:
    void ok_button_clicked();

};

#endif // PAYRENTWIDGET_H
