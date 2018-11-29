#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "player.h"
#include "block.h"
// to be derived to other

class Asset : public Block{
    public:
        Asset(int id,
              Block* (*block)[40],
              Player*owenr ,
              std::string title ,
              int cost,
              int mortgage_value
              );

        virtual ~Asset();
        void change_owner(Player* player);
        Player* get_owner();
        int get_assetcost();
        int get_assetmortgage();
        virtual bool trigger_event(Player* player, int points) = 0 ;

    protected:
        Player* owner;
        std::string title;
        int cost;
        int mortgage_value;
        bool mortgaged = false;


};
#endif // ASSET_H
