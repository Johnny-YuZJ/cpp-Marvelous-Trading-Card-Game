#ifndef enchant_haste_h
#define enchant_haste_h
#include "enchanted_minion.h"
#include <memory>

class Minion;
class Enchantment;

class EnchantHaste: public EnchantedMinion{
public:
    EnchantHaste(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment);
    
    void restoreAction(int i) override;
};


#endif /* enchant_haste_h */
