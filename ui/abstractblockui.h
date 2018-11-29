#ifndef ABSTRACTBLOCKUI_H
#define ABSTRACTBLOCKUI_H

#include <QPushButton>
#include <map>

typedef std::map<std::string, std::string> StyleMap;

class AbstractBlockUI : public QPushButton
{
    Q_OBJECT
public:
    AbstractBlockUI(QWidget* parent = nullptr, int position = 0);
    void setStyle(std::string key, std::string value);
    void applyStyle();
    virtual void render() = 0;
    virtual int token_pos_x() = 0;
    virtual int token_pos_y() = 0;
    //virtual void getGraphicalXCoordinate() = 0;
    //virtual void getGraphicalYCoordinate() = 0;

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    bool event(QEvent *event);

    static const int BLOCK_HEIGHT = 140;
    static const int BLOCK_NORMAL_WIDTH = 80;
    static const int OFFSET_X = 20;
    static const int OFFSET_Y = 20;

    StyleMap style;
    int position;


signals:
    void hovered_enter_with_pos(int pos);
    void hovered_leave_with_pos(int pos);
private slots:
    void hovered_enter_handler();
    void hovered_leave_handler();
};

#endif // ABSTRACTBLOCKUI_H
