#ifndef RAISEDEAD_H_INCLUDED
#define RAISEDEAD_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class RaiseDead: public Spell{
public:
    RaiseDead(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
};

#endif // RAISEDEAD_H_INCLUDED
