#ifndef SUMMONTHREE_H_INCLUDED
#define SUMMONTHREE_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class SummonThree: public Spell{
public:
    SummonThree(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
    void destroy() override;
};

#endif // SUMMONTHREE_H_INCLUDED
