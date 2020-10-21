#include "silence.h"
#include "../minion/minion.h"
#include "../minion/enchanted_minion.h"
#include "../minion/enchant_silence.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

Silence::Silence(std::shared_ptr<Player> owner)
: Enchantment("", "", "Silence", 1, "Enchanted minion cannot use abilities", owner){}

void Silence::enchant(std::shared_ptr<Card> target){
    shared_ptr<Minion> minion = dynamic_pointer_cast<Minion>(target);
    if (minion) {
        auto thisClass = static_pointer_cast<Silence>(Enchantment::shared_from_this());
        
        shared_ptr<EnchantedMinion> enchanted = make_shared<EnchantSilence>(minion, thisClass);
        enchanted->getOwner()->getBoard()->replaceMinion(minion, enchanted);
    } else {
        cerr << "Enchantment target has to be a minion" << endl;
    }
}
