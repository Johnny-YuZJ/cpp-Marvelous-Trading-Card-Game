#include "enchant_giant_strength.h"
#include "../../display/info.h"

EnchantGiantStrength::EnchantGiantStrength(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment)
: EnchantedMinion(innerMinion, enchantment, innerMinion->getAttack() + 2, innerMinion->getDefense() + 2,
                  innerMinion->getAction(), innerMinion->getCardInfo().name, innerMinion->getCardInfo().cost,
                  innerMinion->getCardInfo().desc, innerMinion->getOwner()){}
