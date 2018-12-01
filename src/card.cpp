#include "card.h"

Card::Card(QString explanation, QString type):
explanation(explanation),
type(type)
{
}

QString Card::get_explanation() const{
    return explanation;
}

QString Card::get_type() const{
    return type;
}

Card::~Card(){}
