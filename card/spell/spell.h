#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED

#include <memory>
#include "../card.h"
class Player;
class CardInfo;

class Spell: public Card, public std::enable_shared_from_this<Spell>{
    virtual void cast(std::shared_ptr<Card> target) =0; //default to empty
protected:
    virtual void destroy(); //put into usedCards
    //override it in NoviceFireBall, Summon, SummonThree

public:
    Spell(std::string name, int cost, std::string description, std::shared_ptr<Player> owner);
    virtual ~Spell();

    void play(std::shared_ptr<Card> target) override;
    
    void costIncreasedBy(int i);
    
    CardInfo getCardInfo() override;
};

#endif // SPELL_H_INCLUDED
