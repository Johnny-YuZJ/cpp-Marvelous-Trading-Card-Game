#include "magic_fatigue.h"
#include "../minion/minion.h"
#include "../minion/enchanted_minion.h"
#include "../minion/enchant_magic_fatigue.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

MagicFatigue::MagicFatigue(std::shared_ptr<Player> owner)
: Enchantment("", "", "Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more", owner){}

void MagicFatigue::enchant(std::shared_ptr<Card> target){
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        auto thisClass = static_pointer_cast<MagicFatigue>(Enchantment::shared_from_this());
        
        shared_ptr<EnchantedMinion> enchanted = make_shared<EnchantMagicFatigue>(minion, thisClass);
        enchanted->getOwner()->getBoard()->replaceMinion(minion, enchanted);
    } else {
        cerr << "Enchantment target has to be a minion" << endl;
    }
}
