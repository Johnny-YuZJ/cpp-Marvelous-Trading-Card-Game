#include "summon.h"
#include "../minion/air_elemental.h"
#include "../../player.h"
#include "../../board.h"
#include <string>
#include <iostream>
using namespace std;

//Constructor
Summon::Summon(shared_ptr<Player> owner)
    : Spell("Summon", 1, "Summon a 1/1 air elemental", owner){}

void Summon::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target != nullptr){
        cerr << "Activate ability doesn't need target!" << endl;
        return;
    }
    
    if (getOwner()->getBoard()->hasMinionSlot(getOwner()->getId())){
        shared_ptr<AirElemental> ae = make_shared<AirElemental>(getOwner());
        getOwner()->getBoard()->placeMinion(getOwner()->getId(), ae);
    }
}

//did nothing
void Summon::destroy(){}
