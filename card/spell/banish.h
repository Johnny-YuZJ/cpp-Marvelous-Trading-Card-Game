#ifndef BANISH_H_INCLUDED
#define BANISH_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Banish: public Spell{
public:
    Banish(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};

#endif // BANISH_H_INCLUDED
