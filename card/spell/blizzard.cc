#include "blizzard.h"
#include <string>
#include "../card.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>
using namespace std;

//Constructor
Blizzard::Blizzard(shared_ptr<Player> owner)
    :Spell("Blizzard", 3, "Deal 2 damage to all minions", owner){}

void Blizzard::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target != nullptr){
        cerr << "Blizzard doesn't need target!" << endl;
        return;
    }
    getOwner()->getBoard()->aoe(getOwner()->getId(), 2);
}

