#ifndef PROPERTY_H
#define PROPERTY_H

#include "asset.h"
#include "vector"

using namespace std;

class Property : public Asset{

    public:

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
        Property(
                 Block* (*block)[40],
                 Player*owenr ,
                 QString title ,
                 int cost,
                 int housecost,
                 vector<int> rentlist,
                 Group group);
        ~Property();
        int get_housecost() const;
        int get_house() const;
        int get_hotel() const;
        int get_rent() ;

        bool add_house();
        bool add_hotel();

        bool sell_house();
        bool sell_hotel();


        bool get_monopoly() const;
        void set_monopoly(bool monopoly);
        void update_group_monopoly();
        virtual void update();
        virtual bool can_mortgage();
        virtual void set_mortgage();
        virtual bool trigger_event(Player* player,int points, int& signal);


    private:
        int house;
        int hotel;
        Group group;
        bool monopoly;
        int housecost;
        vector<int> rentlist;
        const int MAX_HOUSE = 4;
        const int MAX_HOTEL = 1;


};

#endif // PROPERTY_H
