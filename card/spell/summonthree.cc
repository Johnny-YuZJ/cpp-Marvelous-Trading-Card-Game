#include "summonthree.h"
#include "../minion/air_elemental.h"
#include "../../player.h"
#include "../../board.h"
#include <string>
#include <iostream>
using namespace std;

//Constructor
SummonThree::SummonThree(shared_ptr<Player> owner)
    : Spell("Summon Three", 2, "Summon up to three 1/1 air elementals", owner){}

void SummonThree::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target != nullptr){
        cerr << "Activate ability doesn't need target!" << endl;
        return;
    }
    //loop to call elementals
    for (int i = 0; i < 3; i++) {
        if (getOwner()->getBoard()->hasMinionSlot(getOwner()->getId())){
            shared_ptr<AirElemental> ae = make_shared<AirElemental>(getOwner());
            getOwner()->getBoard()->placeMinion(getOwner()->getId(), ae);
        } else {
            break;
        }
    }
}

//did nothing
void SummonThree::destroy(){}
