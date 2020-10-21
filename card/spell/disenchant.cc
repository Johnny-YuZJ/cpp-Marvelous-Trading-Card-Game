#include "disenchant.h"
#include "../minion/minion.h"
#include <string>
#include <iostream>
using namespace std;

Disenchant::Disenchant(shared_ptr<Player> owner)
    : Spell("Disenchant", 1, "Destroy the top enchantment on target minion", owner){}

void Disenchant::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target == nullptr){
        cerr << "Disenchant needs target!" << endl;
        return;
    }
    
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        minion->removeTopEnchant();
    } else {
        cerr << "Disenchant target has to be a minion" << endl;
    }
}

