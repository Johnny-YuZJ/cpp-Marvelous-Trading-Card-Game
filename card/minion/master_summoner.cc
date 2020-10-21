#include "master_summoner.h"
#include "../../player.h"
#include "../../board.h"
#include "../spell/summonthree.h"
#include <iostream>

using namespace std;

MasterSummoner::MasterSummoner(shared_ptr<Player> owner): NormalMinion(2, 3, "Master Summoner", 3, "Summon up to three 1/1 air elementals.", owner){
    ability = make_shared<SummonThree>(owner);
}

bool MasterSummoner::canActivateAbility(){
    return true;
}
int MasterSummoner::getActivationCost(){
    return ability->getCost();
}
void MasterSummoner::activateAbility(std::shared_ptr<Minion> t){
    if (canAttack() && ability->canPlay()) {
        useAction();
        ability->play(t);
    } else {
        cout << "This minion does not have enough action or player does not have enough magic" << endl;
    }
}

void MasterSummoner::activationCostIncreasedBy(int i){
    ability->costIncreasedBy(i);
}
