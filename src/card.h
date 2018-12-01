#ifndef CARD_H
#define CARD_H

#include <QString>
using namespace std;

class Card {
    private:

    QString explanation;
    QString type;

    public:

    QString get_explanation() const;
    QString get_type() const;
    Card(QString explanation , QString type);
    ~Card();
};
#endif // CARD_H
