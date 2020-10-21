#include "recharge.h"
#include <string>
#include <iostream>
#include "../../player.h"
#include "../ritual/ritual.h"
using namespace std;

Recharge::Recharge(shared_ptr<Player> owner)
    :Spell("Recharge", 1, "Your ritual gains 3 charges", owner){}

void Recharge::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target != nullptr){
        cerr << "Recharge doesn't need target!" << endl;
        return;
    }
    if (getOwner()->getRitual() != nullptr){
        getOwner()->getRitual()->gainCharge(3);
    }
}

