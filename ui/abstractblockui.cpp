#include "abstractblockui.h"
#include <sstream>
#include <QEvent>
#include <QHoverEvent>

using std::string;
using std::ostringstream;

AbstractBlockUI::AbstractBlockUI(QWidget* parent, int position):
    QPushButton (parent),
    position(position)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

void AbstractBlockUI::setStyle(string key, string value) {
    this->style[key] = value;
}

void AbstractBlockUI::applyStyle() {
    ostringstream s;
    for(StyleMap::iterator i = this->style.begin(); i != this->style.end(); i++) {
        s << i->first << ":" << i->second << ";";
    }

    string style_string = s.str();
    setStyleSheet(QString::fromStdString(style_string));
}

void AbstractBlockUI::hovered_enter_handler() {
    emit hovered_enter_with_pos(position);
}

void AbstractBlockUI::hovered_leave_handler() {
    emit hovered_leave_with_pos(position);
}

void AbstractBlockUI::hoverEnter(QHoverEvent *){
    hovered_enter_handler();
};
void AbstractBlockUI::hoverLeave(QHoverEvent *){
    hovered_leave_handler();
};

bool AbstractBlockUI::event(QEvent *event) {
    switch(event->type())  {
        case QEvent::HoverEnter:
            hoverEnter(static_cast<QHoverEvent*>(event));
            return true;
        case QEvent::HoverLeave:
            hoverLeave(static_cast<QHoverEvent*>(event));
            return true;
        default:
            break;
    }

    return QWidget::event(event);
};
