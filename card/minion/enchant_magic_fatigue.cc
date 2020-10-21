#include "enchant_magic_fatigue.h"
#include "../../display/info.h"
#include "../../player.h"
#include "../../board.h"

EnchantMagicFatigue::EnchantMagicFatigue(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment)
: EnchantedMinion(innerMinion, enchantment, innerMinion->getAttack(), innerMinion->getDefense(),
                  innerMinion->getAction(), innerMinion->getCardInfo().name, innerMinion->getCardInfo().cost,
                  innerMinion->getCardInfo().desc, innerMinion->getOwner()){
    activationCostIncreasedBy(2);
}

void EnchantMagicFatigue::removeTopEnchant(){
    activationCostIncreasedBy(-2);
    getOwner()->getBoard()->replaceMinion(shared_from_this(), innerMinion);
}
