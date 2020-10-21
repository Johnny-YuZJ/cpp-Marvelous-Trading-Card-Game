#include "fire_elemental.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

FireElemental::FireElemental(shared_ptr<Player> owner): NormalMinion(2, 2, "Fire Elemental", 2, "Whenever an opponent's minion enters play, deal 1 damage to it.", owner){}

bool FireElemental::hasTrigger(){
    return true;
}

int FireElemental::getPlayerId(){
    return getOwner()->getId();
}

bool FireElemental::isRitual(){
    return false;
}

void FireElemental::registerTrigger(){
    auto thisClass = static_pointer_cast<FireElemental>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::EnterBoard);
}

void FireElemental::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<FireElemental>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::EnterBoard);
}

void FireElemental::triggerAbility(shared_ptr<Minion> m){
    if (m->getOwner() != getOwner()){
        m->defenseDecreasedBy(1);
    }
}

void FireElemental::triggerAbility(shared_ptr<Player> p){
    // Does nothing
}
