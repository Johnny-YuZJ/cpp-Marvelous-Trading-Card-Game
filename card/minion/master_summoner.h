#ifndef master_summoner_h
#define master_summoner_h
#include "normal_minion.h"
#include <memory>

class Player;
class Card;
class Spell;

class MasterSummoner: public NormalMinion{
    std::shared_ptr<Spell> ability;
public:
    MasterSummoner(std::shared_ptr<Player> owner);
    
    bool canActivateAbility() override;
    int getActivationCost() override;
    void activateAbility(std::shared_ptr<Minion> t) override;
    void activationCostIncreasedBy(int i) override;
};
#endif /* master_summoner_h */
