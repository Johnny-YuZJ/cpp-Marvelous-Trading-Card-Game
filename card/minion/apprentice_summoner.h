#ifndef apprentice_summoner_h
#define apprentice_summoner_h
#include "normal_minion.h"
#include <memory>

class Player;
class Card;
class Spell;

class ApprenticeSummoner: public NormalMinion{
    std::shared_ptr<Spell> ability;
public:
    ApprenticeSummoner(std::shared_ptr<Player> owner);
    
    bool canActivateAbility() override;
    int getActivationCost() override;
    void activateAbility(std::shared_ptr<Minion> t) override;
    void activationCostIncreasedBy(int i) override;
};
#endif /* apprentice_summoner_h */
