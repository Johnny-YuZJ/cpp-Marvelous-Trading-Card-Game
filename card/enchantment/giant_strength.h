#ifndef giant_strength_h
#define giant_strength_h
#include "enchantment.h"
#include <memory>

class Player;
class Card;

class GiantStrength: public Enchantment{
public:
    GiantStrength(std::shared_ptr<Player> owner);
    
    void enchant(std::shared_ptr<Card> target) override;
};

#endif /* giant_strength_h */
