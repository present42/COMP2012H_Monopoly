#ifndef PROPERTY_H
#define PROPERTY_H

#include "asset.h"


class Property : public Asset{
    enum Group{
        Brown,
        LightBlue,
        Pink,
        Orange,
        Red,
        Yellow,
        Green,
        Blue
    };

    private:
        int rentlist[6];
        int house;
        int hotel;
        Group group;
        bool monopoly;
        const int MAX_HOUSE = 4;
        const int MAX_HOTEL = 1;

    public:
        Property(int id,
                 Block* (*block)[40],
                 Player*owenr ,
                 std::string title ,
                 int cost,
                 int mortgage_value,
                 int rentlist[6],
                 Group group);
        ~Property();
        int get_house();
        int get_hotel();
        int get_rent();

        bool add_house();
        bool add_hotel();
        bool get_monopoly() const;
        void set_monopoly(bool monopoly);
        void update_group_monopoly();

        virtual bool trigger_event(Player* player,int points);


};

#endif // PROPERTY_H
