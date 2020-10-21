#include "auraofpower.h"
#include <string>
#include "../card.h"
#include <iostream>
#include "../minion/minion.h"
#include "../../player.h"
#include "../../board.h"
using namespace std;


//Constructor
AuraOfPower::AuraOfPower(shared_ptr<Player> owner)
    :Ritual("Aura of Power",1,"Whenever a minion enter a play under your control, it gains +1/+1",owner,1,4){}

//return the id of the owner
int AuraOfPower::getPlayerId(){
    return getOwner()->getId();
}

//true if it is ritual, else false
bool AuraOfPower::isRitual(){
    return true;
}

//register to type of trigger
void AuraOfPower::registerTrigger(){
    auto thisClass = static_pointer_cast<AuraOfPower>(Ritual::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::EnterBoard);
}

//unregister to triggers
void AuraOfPower::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<AuraOfPower>(Ritual::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::EnterBoard);
}

//ability trigered when any minion enter
void AuraOfPower::triggerAbility(shared_ptr<Minion> m){
    if(this->canTrigger()){
            if(m->getOwner()->getId() == this->getOwner()->getId()){
                this->chargeDecreasedBy(this->getActivationCost());
                m->defenseIncreasedBy(1);
                m->attackIncreasedBy(1);
            }
    }
}

//nothing happens at start or end turn
void AuraOfPower::triggerAbility(shared_ptr<Player> p){}


