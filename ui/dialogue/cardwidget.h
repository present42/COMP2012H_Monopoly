#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    CardWidget(QWidget* parent = nullptr);
    ~CardWidget();

    void setInstruction(QString instruction);
    void setReader(int id);

private:
    QLabel* reader;
    QLabel* instruction;

    QPushButton* ok_button;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

private slots:
    void ok_button_clicked_handler();

signals:
    void ok_button_clicked();
};

#endif // CARDWIDGET_H
