#include "enchantment.h"
#include "../../display/info.h"
#include "../../player.h"
#include <iostream>

using namespace std;

Enchantment::Enchantment(std::string leftCorner, std::string rightCorner,
                         std::string name, int cost, std::string description, std::shared_ptr<Player> owner)
:leftCorner(leftCorner), rightCorner(rightCorner), Card("Enchantment", name, cost, description, owner){}

CardInfo Enchantment::getCardInfo(){
    CardInfo info;
    info.ability_cost = -1;
    info.cost = cost;
    info.desc = description;
    info.leftCorner = leftCorner;
    info.rightCorner = rightCorner;
    info.name = name;
    info.type = type;
    
    return info;
}

void Enchantment::play(shared_ptr<Card> target){
    if (canPlay()) {
        enchant(target);
        getOwner()->useMagic(this->cost);
        getOwner()->removeFromHandDeck(shared_from_this());
    } else {
        cout<<"Don't have enough magic" << endl;
    }
}
