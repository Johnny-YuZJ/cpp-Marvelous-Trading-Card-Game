#include "standstill.h"
#include <string>
#include "../card.h"
#include "../../player.h"
#include "../minion/minion.h"
#include "../../board.h"
#include <iostream>
using namespace std;

//Constructor
Standstill::Standstill(shared_ptr<Player> owner)
    :Ritual("Standstill",3,"Whenever a minion enter a play, destroy it",owner,2,4){}

//return the id of the owner
int Standstill::getPlayerId(){
    return getOwner()->getId();
}

//true if it is ritual, else false
bool Standstill::isRitual(){
    return true;
}

//register to type of trigger
void Standstill::registerTrigger(){
    auto thisClass = static_pointer_cast<Standstill>(Ritual::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::EnterBoard);
}

//unregister to triggers
void Standstill::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<Standstill>(Ritual::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::EnterBoard);
}

//destroy minion when it enter or leave
void Standstill::triggerAbility(shared_ptr<Minion> m){
    if(this->canTrigger()){
        this->chargeDecreasedBy(this->getActivationCost());
        m->die();
    }
}

//ability trigered at the start turn
void Standstill::triggerAbility(shared_ptr<Player> p){}

