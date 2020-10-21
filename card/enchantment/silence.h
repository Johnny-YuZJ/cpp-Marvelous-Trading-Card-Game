#ifndef silence_h
#define silence_h
#include "enchantment.h"
#include <memory>

class Player;
class Card;

class Silence: public Enchantment{
public:
    Silence(std::shared_ptr<Player> owner);
    
    void enchant(std::shared_ptr<Card> target) override;
};


#endif /* silence_h */
