#ifndef enrage_h
#define enrage_h

#include "enchantment.h"
#include <memory>

class Player;
class Card;

class Enrage: public Enchantment{
public:
    Enrage(std::shared_ptr<Player> owner);
    
    void enchant(std::shared_ptr<Card> target) override;
};

#endif
