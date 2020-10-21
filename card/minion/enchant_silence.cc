#include "enchant_silence.h"
#include "../../display/info.h"

EnchantSilence::EnchantSilence(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment)
: EnchantedMinion(innerMinion, enchantment, innerMinion->getAttack(), innerMinion->getDefense(),
                  innerMinion->getAction(), innerMinion->getCardInfo().name, innerMinion->getCardInfo().cost,
                  innerMinion->getCardInfo().desc, innerMinion->getOwner()){}

bool EnchantSilence::canActivateAbility(){
    return false;
}
