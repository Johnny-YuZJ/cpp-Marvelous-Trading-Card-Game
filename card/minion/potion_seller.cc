#include "potion_seller.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

PotionSeller::PotionSeller(shared_ptr<Player> owner): NormalMinion(1, 3, "Potion Seller", 2, "At the end of your turn, all your minions gain +0/+1.", owner){}

bool PotionSeller::hasTrigger(){
    return true;
}

int PotionSeller::getPlayerId(){
    return getOwner()->getId();
}

bool PotionSeller::isRitual(){
    return false;
}

void PotionSeller::registerTrigger(){
    auto thisClass = static_pointer_cast<PotionSeller>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::EndTurn);
}

void PotionSeller::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<PotionSeller>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::EndTurn);
}

void PotionSeller::triggerAbility(shared_ptr<Minion> m){
    // Does nothing
}

void PotionSeller::triggerAbility(shared_ptr<Player> p){
    if (p == getOwner()) {
        auto minions = getOwner()->getBoard()->getMinions(getOwner()->getId());
        for (auto& minion : minions) {
            minion->defenseIncreasedBy(1);
        }
    }
}
