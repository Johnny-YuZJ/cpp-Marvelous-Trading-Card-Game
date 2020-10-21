#include "darkritual.h"
#include <string>
#include "../card.h"
#include <iostream>
#include "../../board.h"
#include "../../player.h"
#include "../minion/minion.h"
using namespace std;

//Constructor
DarkRitual::DarkRitual(shared_ptr<Player> owner)
:Ritual("Dark Ritual",0,"At the start of your turn, gain 1 magic",owner, 1, 5){}

//return the id of the owner
int DarkRitual::getPlayerId(){
    return getOwner()->getId();
}

//true if it is ritual, else false
bool DarkRitual::isRitual(){
    return true;
}

//register to type of trigger
void DarkRitual::registerTrigger(){
    auto thisClass = static_pointer_cast<DarkRitual>(Ritual::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::StartTurn);
}

//unregister to triggers
void DarkRitual::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<DarkRitual>(Ritual::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::StartTurn);
}

//nothing triggered when any minion enter or leave
void DarkRitual::triggerAbility(shared_ptr<Minion> m){}

//ability trigered at the start turn
void DarkRitual::triggerAbility(shared_ptr<Player> p){
    if(this->canTrigger() && p->getId()==this->getOwner()->getId()){
        this->chargeDecreasedBy(this->getActivationCost());
        p->gainMagic();
    }
}

