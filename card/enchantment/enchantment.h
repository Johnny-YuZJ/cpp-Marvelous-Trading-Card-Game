#ifndef Enchantment_h
#define Enchantment_h
#include "../card.h"
#include <string>
#include <memory>

class Player;
class CardInfo;

class Enchantment: public Card, public std::enable_shared_from_this<Enchantment>{
    std::string leftCorner;
    std::string rightCorner;
protected:
    virtual void enchant(std::shared_ptr<Card> target)=0;
public:
    Enchantment(std::string leftCorner, std::string rightCorner, std::string name, int cost, std::string description, std::shared_ptr<Player> owner);
    
    void play(std::shared_ptr<Card> target) override;
    
    CardInfo getCardInfo() override;
};

#endif /* Enchantment_h */
