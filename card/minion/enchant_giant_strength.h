#ifndef enchant_giant_strength_h
#define enchant_giant_strength_h
#include "enchanted_minion.h"
#include <memory>

class Minion;
class Enchantment;

class EnchantGiantStrength: public EnchantedMinion{
public:
    EnchantGiantStrength(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment);
};

#endif /* enchant_giant_strength_h */
