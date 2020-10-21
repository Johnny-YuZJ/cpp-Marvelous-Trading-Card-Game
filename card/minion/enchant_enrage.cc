#include "enchant_enrage.h"
#include "../../display/info.h"

EnchantEnrage::EnchantEnrage(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment)
: EnchantedMinion(innerMinion, enchantment, innerMinion->getAttack() * 2, innerMinion->getDefense() * 2,
                  innerMinion->getAction(), innerMinion->getCardInfo().name, innerMinion->getCardInfo().cost,
                  innerMinion->getCardInfo().desc, innerMinion->getOwner()){}
