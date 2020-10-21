#include "enchanted_minion.h"
#include "../../display/info.h"
#include "../../player.h"
#include "../../board.h"
#include "../enchantment/enchantment.h"
#include "../card.h"
#include <string>
#include <iostream>

using namespace std;

EnchantedMinion::EnchantedMinion(shared_ptr<Minion> innerMinion, shared_ptr<Enchantment> enchantment, int attackVal, int defense, int action, string name, int cost,
                           string description, shared_ptr<Player> owner)
:innerMinion(innerMinion), enchantment(enchantment),
Minion(attackVal, defense, action, "Enchantment", name, cost, description, owner){}

void EnchantedMinion::play(shared_ptr<Card> target){
    cerr << "There must be something wrong. Enchanted minion cannot be played from hand deck" << endl;
}

//decorators
void EnchantedMinion::die(){
    removeTopEnchant();
    innerMinion->die();
}

bool EnchantedMinion::canActivateAbility() {
    return innerMinion->canActivateAbility();
}

void EnchantedMinion::restoreAction(int i){
    innerMinion->restoreAction(i);
}

int EnchantedMinion::getAction() {
    return innerMinion->getAction();
}

void EnchantedMinion::useAction(){
    innerMinion->useAction();
}

void EnchantedMinion::activationCostIncreasedBy(int i){
    innerMinion->activationCostIncreasedBy(i);
}

int EnchantedMinion::getActivationCost(){
    return innerMinion->getActivationCost();
}

//activate Ability to the target minion, need to check canActivate
void EnchantedMinion::activateAbility(std::shared_ptr<Minion> t){
    if (canActivateAbility() && canAttack()) {
        innerMinion->activateAbility(t);
    } else {
        cout << "This minion is either silenced or does not have an activated ability or does not have action" << endl;
    }
}

//called by Unsummon
void EnchantedMinion::returnDeck(){
    getOwner()->getBoard()->replaceMinion(shared_from_this(), innerMinion);
    innerMinion->returnDeck();
}

void EnchantedMinion::removeTopEnchant(){
    getOwner()->getBoard()->replaceMinion(shared_from_this(), innerMinion);
}

vector<CardInfo> EnchantedMinion::getEnchantmentInfo(){
    vector<CardInfo> innerEnchantmentInfo = innerMinion->getEnchantmentInfo();
    innerEnchantmentInfo.push_back(enchantment->getCardInfo());
    return innerEnchantmentInfo;
}
