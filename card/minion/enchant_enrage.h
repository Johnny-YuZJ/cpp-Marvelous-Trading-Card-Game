#ifndef enchant_enrage_h
#define enchant_enrage_h
#include "enchanted_minion.h"
#include <memory>

class Minion;
class Enchantment;

class EnchantEnrage: public EnchantedMinion{
public:
    EnchantEnrage(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment);
};

#endif /* enchant_enrage_h */
