#ifndef magic_fatigue_h
#define magic_fatigue_h
#include "enchantment.h"
#include <memory>

class Player;
class Card;

class MagicFatigue: public Enchantment{
public:
    MagicFatigue(std::shared_ptr<Player> owner);
    
    void enchant(std::shared_ptr<Card> target) override;
};


#endif /* magic_fatigue_h */
