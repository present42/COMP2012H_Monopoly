#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "player.h"
#include "block.h"
// to be derived to other

class Asset : public Block{
    public:
        Asset(
              Block* (*block)[40],
              Player*owenr ,
              QString title ,
              int cost
              );

        virtual ~Asset();
        void change_owner(Player* player);
        Player* get_owner();
        int get_assetcost();
        int get_assetmortgage();
        void demortgage();
        virtual void set_mortgage();
        virtual bool trigger_event(Player* player, int points);

    protected:
        Player* owner;
        QString title;
        int cost;
        int mortgage_value;
        bool mortgaged = false;

};
#endif // ASSET_H
