#ifndef ENDTURNWIDGET_H
#define ENDTURNWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class EndTurnWidget : public QWidget
{
    Q_OBJECT
public:
    EndTurnWidget(QWidget* parent = nullptr);
    ~EndTurnWidget();
    QPushButton* get_end_turn_button();
    void setPlayerID(int id);
private:
    QPushButton* end_turn_button;
    QLabel* id_label;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

signals:
    void end_turn_button_clicked();

private slots:

};

#endif // ENDTURNWIDGET_H
