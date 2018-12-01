#ifndef CARD_H
#define CARD_H

#include <QString>
using namespace std;

class Card {
    private:
    int id;
    QString explanation;
    QString type;

    public:
    int get_id() const;
    QString get_explanation() const;
    QString get_type() const;
    Card(int id, QString explanation , QString type);
    ~Card();
};
#endif // CARD_H
