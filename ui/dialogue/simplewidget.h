#ifndef SIMPLEWIDGET_H
#define SIMPLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SimpleWidget : public QWidget
{
    Q_OBJECT
public:
    SimpleWidget(QWidget* parent = nullptr);
    ~SimpleWidget();

    void setExplanation(QString instruction);

private:
    QLabel* explanation;
    QPushButton* ok_button;

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

private slots:
    void ok_button_clicked_handler();

signals:
    void ok_button_clicked();
};

#endif // SIMPLEWIDGET_H
