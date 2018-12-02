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
    int getType() {
        return type;
    }

    void setType(int type) {
        this->type = type;
    }
private:
    QLabel* explanation;
    QPushButton* ok_button;
    int type = 6; // 6: do nothing
                  // 11: "Choose the place in which you want to build"

    const static int BLOCK_NORMAL_WIDTH = 80;
    const static int BLOCK_HEIGHT = 140;
    const static int OFFSET = 20;

private slots:
    void ok_button_clicked_handler();

signals:
    void ok_button_clicked(int type);
};

#endif // SIMPLEWIDGET_H
