#include "apprentice_summoner.h"
#include "../../player.h"
#include "../../board.h"
#include "../spell/summon.h"
#include <iostream>

using namespace std;

ApprenticeSummoner::ApprenticeSummoner(shared_ptr<Player> owner): NormalMinion(1, 1, "Apprentice Summoner", 1, "Summon a 1/1 air elemental", owner){
    ability = make_shared<Summon>(owner);
}

bool ApprenticeSummoner::canActivateAbility(){
    return true;
}
int ApprenticeSummoner::getActivationCost(){
    return ability->getCost();
}
void ApprenticeSummoner::activateAbility(std::shared_ptr<Minion> t){
    if (canAttack() && ability->canPlay()) {
        useAction();
        ability->play(t);
    } else {
        cout << "This minion does not have enough action or player does not have enough magic" << endl;
    }
}

void ApprenticeSummoner::activationCostIncreasedBy(int i){
    ability->costIncreasedBy(i);
}
