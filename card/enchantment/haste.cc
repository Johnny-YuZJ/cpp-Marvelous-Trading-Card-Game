#include "haste.h"
#include "../minion/minion.h"
#include "../minion/enchanted_minion.h"
#include "../minion/enchant_haste.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

Haste::Haste(std::shared_ptr<Player> owner)
: Enchantment("", "", "Haste", 1, "Enchanted minion gains +1 action each turn", owner){}

void Haste::enchant(std::shared_ptr<Card> target){
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        auto thisClass = static_pointer_cast<Haste>(Enchantment::shared_from_this());
        
        shared_ptr<EnchantedMinion> enchanted = make_shared<EnchantHaste>(minion, thisClass);
        enchanted->getOwner()->getBoard()->replaceMinion(minion, enchanted);
    } else {
        cerr << "Enchantment target has to be a minion" << endl;
    }
}
