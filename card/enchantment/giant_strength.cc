#include "giant_strength.h"
#include "../minion/minion.h"
#include "../minion/enchanted_minion.h"
#include "../minion/enchant_giant_strength.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

GiantStrength::GiantStrength(std::shared_ptr<Player> owner)
: Enchantment("+2", "+2", "Giant Strength", 1, "", owner){}

void GiantStrength::enchant(std::shared_ptr<Card> target){
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        auto thisClass = static_pointer_cast<GiantStrength>(Enchantment::shared_from_this());
        
        shared_ptr<EnchantedMinion> enchanted = make_shared<EnchantGiantStrength>(minion, thisClass);
        enchanted->getOwner()->getBoard()->replaceMinion(minion, enchanted);
    } else {
        cerr << "Enchantment target has to be a minion" << endl;
    }
}
