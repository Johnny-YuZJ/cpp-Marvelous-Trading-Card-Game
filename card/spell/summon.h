#ifndef SUMMON_H_INCLUDED
#define SUMMON_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Summon: public Spell{
public:
    Summon(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
    void destroy() override;
};


#endif // SUMMON_H_INCLUDED
