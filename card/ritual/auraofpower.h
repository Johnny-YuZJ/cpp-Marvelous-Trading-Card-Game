#ifndef AURAOFPOWER_H_INCLUDED
#define AURAOFPOWER_H_INCLUDED

#include "ritual.h"
#include "../trigger.h"
#include <memory>
class Player;
class Minion;


class AuraOfPower: public Ritual, public Trigger{
public:
    AuraOfPower(std::shared_ptr<Player> owner);
    int getPlayerId() override;
    bool isRitual() override;
    void registerTrigger() override;
    void unRegisterTrigger() override;
    void triggerAbility(std::shared_ptr<Minion> m) override;
    void triggerAbility(std::shared_ptr<Player> p) override;
} ;


#endif // AURAOFPOWER_H_INCLUDED
