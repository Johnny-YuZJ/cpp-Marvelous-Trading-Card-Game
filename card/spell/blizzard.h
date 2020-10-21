#ifndef BLIZZARD_H_INCLUDED
#define BLIZZARD_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Blizzard: public Spell{
public:
    Blizzard(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};

#endif // BLIZZARD_H_INCLUDED
