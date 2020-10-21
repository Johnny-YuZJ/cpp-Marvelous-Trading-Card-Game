#include "bone_golem.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

BoneGolem::BoneGolem(shared_ptr<Player> owner): NormalMinion(1, 3, "Bone Golem", 2, "Gain +1/+1 whenever a minion leaves play.", owner){}

bool BoneGolem::hasTrigger(){
    return true;
}

int BoneGolem::getPlayerId(){
    return getOwner()->getId();
}

bool BoneGolem::isRitual(){
    return false;
}

void BoneGolem::registerTrigger(){
    auto thisClass = static_pointer_cast<BoneGolem>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->attach(thisClass, GameEvent::LeaveBoard);
}

void BoneGolem::unRegisterTrigger(){
    auto thisClass = static_pointer_cast<BoneGolem>(NormalMinion::shared_from_this());
    getOwner()->getBoard()->detach(thisClass, GameEvent::LeaveBoard);
}

void BoneGolem::triggerAbility(shared_ptr<Minion> m){
    attackVal++;
    defense++;
}

void BoneGolem::triggerAbility(shared_ptr<Player> p){
    // Does nothing
}
