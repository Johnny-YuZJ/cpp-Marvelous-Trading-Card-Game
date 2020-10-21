#include "novice_pyromancer.h"
#include "../../player.h"
#include "../../board.h"
#include "../spell/novicefireball.h"
#include <iostream>

using namespace std;

NovicePyromancer::NovicePyromancer(shared_ptr<Player> owner): NormalMinion(0, 1, "Novice Pyromancer", 1, "Deal 1 damage to target minion", owner){
    ability = make_shared<NoviceFireBall>(owner);
}

bool NovicePyromancer::canActivateAbility(){
    return true;
}
int NovicePyromancer::getActivationCost(){
    return ability->getCost();
}
void NovicePyromancer::activateAbility(std::shared_ptr<Minion> t){
    if (canAttack() && ability->canPlay()) {
        useAction();
        ability->play(t);
    } else {
        cout << "This minion does not have enough action or player does not have enough magic" << endl;
    }
}

void NovicePyromancer::activationCostIncreasedBy(int i){
    ability->costIncreasedBy(i);
}
