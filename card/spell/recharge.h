#ifndef RECHARGE_H_INCLUDED
#define RECHARGE_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class Recharge: public Spell{
public:
    Recharge(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};


#endif // RECHARGE_H_INCLUDED
