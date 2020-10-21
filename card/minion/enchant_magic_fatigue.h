#ifndef enchant_magic_fatigue_h
#define enchant_magic_fatigue_h
#include "enchanted_minion.h"
#include <memory>

class Minion;
class Enchantment;

class EnchantMagicFatigue: public EnchantedMinion{
public:
    EnchantMagicFatigue(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment);
    
    void removeTopEnchant() override;
};


#endif /* enchant_magic_fatigue_h */
