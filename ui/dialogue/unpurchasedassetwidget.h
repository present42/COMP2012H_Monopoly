#ifndef UNPURCHASEDASSETWIDGET_H
#define UNPURCHASEDASSETWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class UnpurchasedAssetWidget : public QWidget
{
    Q_OBJECT
public:
    UnpurchasedAssetWidget(QWidget* parent = nullptr);
    ~UnpurchasedAssetWidget();
    void setPrice(int price = 0);
    void setPreview(int position = 0);
    QPushButton* getPurchaseButton();
private:
    QPushButton* purchase_button;
    QPushButton* auction_button;
    QLabel* instruction;
    QLabel* price;
    QLabel* preview;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

signals:
    void purchase_button_clicked();
    void auction_button_clicked();

private slots:
    void purchase();

};

#endif // UNPURCHASEDASSETWIDGET_H
