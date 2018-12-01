#include "card.h"

Card::Card(int id, QString explanation, QString type):
id(id),
explanation(explanation),
type(type)
{
}

int Card::get_id() const{
    return id;
}
QString Card::get_explanation() const{
    return explanation;
}

QString Card::get_type() const{
    return type;
}

Card::~Card(){}
