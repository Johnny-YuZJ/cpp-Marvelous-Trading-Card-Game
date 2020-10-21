#include <iostream>
#include "normal_minion.h"
#include "../../player.h"
#include "../../board.h"
#include "../../display/info.h"

using namespace std;

NormalMinion::NormalMinion(int attackVal, int defense, string name, int cost,
                           string description, shared_ptr<Player> owner)
:action(0), Minion(attackVal, defense, 0, "Minion", name, cost, description, owner){}

void NormalMinion::setDefense(int i) {
    defense = i;
}

bool NormalMinion::canPlay(){
    bool hasEnoughMagic = getOwner()->getBoard()->isTesting() ? true : getOwner()->getMagic() >= cost;
    if(hasEnoughMagic && getOwner()->getBoard()->hasMinionSlot(getOwner()->getId())){
        return true;
    } else {
        return false;
    }
}

void NormalMinion::play(shared_ptr<Card> target) {
    if (target != nullptr) {
        cerr << "This is a minion. Don't need target!" << endl;
        return;
    }
    if (canPlay()) {
        getOwner()->useMagic(this->cost);
        auto c = getOwner()->removeFromHandDeck(shared_from_this());
        shared_ptr<NormalMinion> nm = dynamic_pointer_cast<NormalMinion>(c);
        getOwner()->getBoard()->placeMinion(getOwner()->getId(), nm);
    }
}

bool NormalMinion::hasTrigger(){
    return false; // default false
}

void NormalMinion::die(){
    auto nm = getOwner()->getBoard()->removeMinion(getOwner()->getId(), shared_from_this());
    getOwner()->putToGraveYard(nm);
}

bool NormalMinion::canActivateAbility(){
    return false;
}

int NormalMinion::getAction(){
    return action;
}

void NormalMinion::useAction(){
    action--;
}

void NormalMinion::restoreAction(int i){
    action = 1 + i;
}

void NormalMinion::activationCostIncreasedBy(int i){}

int NormalMinion::getActivationCost(){
    return 0;
}

void NormalMinion::activateAbility(std::shared_ptr<Minion> t){
    // does nothing
    cout << "This minion does not have activated ability" << endl;
}

void NormalMinion::returnDeck(){
    auto m = getOwner()->getBoard()->removeMinion(getOwner()->getId(), shared_from_this());
    getOwner()->putToHandDeck(m);
}

void NormalMinion::removeTopEnchant(){}

vector<CardInfo> NormalMinion::getEnchantmentInfo(){
    vector<CardInfo> enchantmentInfo;
    return enchantmentInfo;
}
