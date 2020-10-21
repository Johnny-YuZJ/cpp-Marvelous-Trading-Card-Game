#ifndef UNSUMMON_H_INCLUDED
#define UNSUMMON_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Unsummon: public Spell{
public:
    Unsummon(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};

#endif // UNSUMMON_H_INCLUDED
