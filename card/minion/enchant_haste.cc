#include "enchant_haste.h"
#include "../../display/info.h"

EnchantHaste::EnchantHaste(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment)
: EnchantedMinion(innerMinion, enchantment, innerMinion->getAttack(), innerMinion->getDefense(),
                  innerMinion->getAction(), innerMinion->getCardInfo().name, innerMinion->getCardInfo().cost,
                  innerMinion->getCardInfo().desc, innerMinion->getOwner()){}

void EnchantHaste::restoreAction(int i){
    innerMinion->restoreAction(i + 1);
}
