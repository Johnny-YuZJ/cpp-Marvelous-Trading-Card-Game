#ifndef DARKRITUAL_H_INCLUDED
#define DARKRITUAL_H_INCLUDED

#include "ritual.h"
#include "../trigger.h"
#include <memory>
class Player;
class Minion;

class DarkRitual: public Ritual, public Trigger{
public:
    DarkRitual(std::shared_ptr<Player> owner);
    int getPlayerId() override;
    bool isRitual() override;
    void registerTrigger() override;
    void unRegisterTrigger() override;
    void triggerAbility(std::shared_ptr<Minion> m) override;
    void triggerAbility(std::shared_ptr<Player> p) override;
} ;

#endif // DARKRITUAL_H_INCLUDED
