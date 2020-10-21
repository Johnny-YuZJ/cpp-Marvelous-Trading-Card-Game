#include "spell.h"
#include  <vector>
#include <string>
#include "../../player.h"
#include "../card.h"
#include <iostream>
#include "../../display/info.h"
using namespace std;

//Constructor
Spell::Spell(string name, int cost, string description, shared_ptr<Player> owner)
    : Card("Spell", name, cost, description, owner) {}

//Destructor
Spell::~Spell() {}

//put to used card
void Spell::destroy(){
    auto c = getOwner()->removeFromHandDeck(shared_from_this());
    getOwner()->addToUsedCards(c);
}

void Spell::play(shared_ptr<Card> target){
    if(canPlay()){
        getOwner()->useMagic(this->cost);
        destroy();
        cast(target);
    } else {
        cout<<"Don't have enough magic"<<endl;
    }
}

void Spell::costIncreasedBy(int i){
    cost += i;
}

CardInfo Spell::getCardInfo() {
    CardInfo info;
    info.ability_cost = -1;
    info.cost = cost;
    info.desc = description;
    info.leftCorner = "";
    info.rightCorner = "";
    info.name = name;
    info.type = type;
    
    return info;
}
