#ifndef novice_pyromancer_h
#define novice_pyromancer_h
#include "normal_minion.h"
#include <memory>

class Player;
class Card;
class Spell;

class NovicePyromancer: public NormalMinion{
    std::shared_ptr<Spell> ability;
public:
    NovicePyromancer(std::shared_ptr<Player> owner);
    
    bool canActivateAbility() override;
    int getActivationCost() override;
    void activateAbility(std::shared_ptr<Minion> t) override;
    void activationCostIncreasedBy(int i) override;
};

#endif /* novice_pyromancer_h */
