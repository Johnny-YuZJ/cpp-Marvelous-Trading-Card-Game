#include "ritual.h"
#include <vector>
#include <string>
#include "../../player.h"
#include "../card.h"
#include "../../display/info.h"
#include "../../board.h"
#include <iostream>
using namespace std;

//Constructor
Ritual::Ritual(string name, int cost, string description, shared_ptr<Player> owner, int activationCost, int charge)
: Card("Ritual", name, cost, description, owner), activationCost{activationCost}, charge{charge}{}

//Destructor
Ritual::~Ritual(){}

void Ritual::gainCharge(int i){
    charge += i;
}

void Ritual::removeThis(){
    getOwner()->removeTheRitual();
}

bool Ritual::canTrigger(){
    if(charge < activationCost){
        return false;
    } else {
        return true;
    }
}

int Ritual::getActivationCost(){
    return activationCost;
}

int Ritual::getCharge(){
    return charge;
}

void Ritual::chargeDecreasedBy(int i){
    charge -= i;
}

void Ritual::chargeIncreasedBy(int i){
    charge += i;
}

//Place ritual
void Ritual::play(std::shared_ptr<Card> target){
    if (target != nullptr){
        cerr<<"This is ritual. Don't need target!"<<endl;
        return;
    }
    if (canPlay()){
        getOwner()->useMagic(this->cost);
        getOwner()->removeTheRitual(); //remove previous ritual
        getOwner()->setRitual(shared_from_this());
        getOwner()->removeFromHandDeck(shared_from_this());
    } else {
        cout<<"Player does not have enough magic to play ritual"<<endl;
    }
}

//get cardInfo
CardInfo Ritual::getCardInfo(){
    CardInfo info;
    info.ability_cost = activationCost;
    info.cost = cost;
    info.desc = description;
    info.leftCorner = "";
    info.rightCorner = to_string(charge);
    info.name = name;
    info.type = type;

    return info;
}

