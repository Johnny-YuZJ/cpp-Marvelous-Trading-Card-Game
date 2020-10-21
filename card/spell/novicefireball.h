#ifndef NOVICEFIREBALL_H_INCLUDED
#define NOVICEFIREBALL_H_INCLUDED

#include <memory>
#include "spell.h"
class Player;

class NoviceFireBall: public Spell{
public:
    NoviceFireBall(std::shared_ptr<Player> owner);
    void cast(std::shared_ptr<Card> target) override;
    void destroy() override;
};

#endif // NOVICEFIREBALL_H_INCLUDED
