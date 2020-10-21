#include "enrage.h"
#include "../minion/minion.h"
#include "../minion/enchanted_minion.h"
#include "../minion/enchant_enrage.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

Enrage::Enrage(std::shared_ptr<Player> owner)
: Enchantment("*2", "*2", "Enrage", 2, "", owner){}

void Enrage::enchant(std::shared_ptr<Card> target){
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        auto thisClass = static_pointer_cast<Enrage>(Enchantment::shared_from_this());
        
        shared_ptr<EnchantedMinion> enchanted = make_shared<EnchantEnrage>(minion, thisClass);
        enchanted->getOwner()->getBoard()->replaceMinion(minion, enchanted);
    } else {
        cerr << "Enchantment target has to be a minion" << endl;
    }
}
