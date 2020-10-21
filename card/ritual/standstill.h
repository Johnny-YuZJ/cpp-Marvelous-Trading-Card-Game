#ifndef STANDSTILL_H_INCLUDED
#define STANDSTILL_H_INCLUDED

#include "ritual.h"
#include "../trigger.h"
#include <memory>
class Player;
class Minion;

class Standstill: public Ritual, public Trigger{
public:
    Standstill(std::shared_ptr<Player> owner);
    int getPlayerId() override;
    bool isRitual() override;
    void registerTrigger() override;
    void unRegisterTrigger() override;
    void triggerAbility(std::shared_ptr<Minion> m) override;
    void triggerAbility(std::shared_ptr<Player> p) override;
} ;



#endif // STANDSTILL_H_INCLUDED
