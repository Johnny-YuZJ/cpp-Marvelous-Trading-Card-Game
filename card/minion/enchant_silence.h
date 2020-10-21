#ifndef enchant_silence_h
#define enchant_silence_h
#include "enchanted_minion.h"
#include <memory>

class Minion;
class Enchantment;

class EnchantSilence: public EnchantedMinion{
public:
    EnchantSilence(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment);
    
    bool canActivateAbility() override;
};


#endif /* enchant_silence_h */
