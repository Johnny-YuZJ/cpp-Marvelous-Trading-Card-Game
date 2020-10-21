#ifndef haste_h
#define haste_h
#include "enchantment.h"
#include <memory>

class Player;
class Card;

class Haste: public Enchantment{
public:
    Haste(std::shared_ptr<Player> owner);
    
    void enchant(std::shared_ptr<Card> target) override;
};


#endif /* haste_h */
