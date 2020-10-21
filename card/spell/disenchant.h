#ifndef DISENCHANT_H_INCLUDED
#define DISENCHANT_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Disenchant: public Spell{
public:
    Disenchant(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};

#endif // DISENCHANT_H_INCLUDED
