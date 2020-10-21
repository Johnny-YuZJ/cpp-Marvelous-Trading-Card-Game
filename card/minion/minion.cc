#include "minion.h"
#include <iostream>
#include <string>
#include "../card.h"
#include "../../player.h"
#include "../../display/info.h"
using namespace std;

Minion::Minion(int attackVal, int defense, int action, string type, string name,
               int cost, string description, shared_ptr<Player> owner)
    :Card(type, name, cost, description, owner), attackVal(attackVal), defense(defense){}

//check action
bool Minion::canAttack(){
    if (getAction() <= 0) {
        return false;
    }
    return true;
}

void Minion::attack(shared_ptr<Player> p){
    if (canAttack()){
        useAction();
        p->hpDecreasedBy(getAttack());
    } else {
        cout << "The minion does not have enough actions to attack" << endl;
    }
}

void Minion::attack(shared_ptr<Minion> m){
    if (canAttack()){
        useAction();
        m->defenseDecreasedBy(getAttack());
        this->defenseDecreasedBy(m->getAttack());
    } else {
        cout << "The minion does not have enough actions to attack" << endl;
    }
}

// need to handle death
void Minion::defenseDecreasedBy(int damage){
    defense -= damage;
    if (defense <= 0) {
        die();
    }
}

void Minion::defenseIncreasedBy(int damage){
    defense += damage;
}

void Minion::attackIncreasedBy(int i){
    attackVal += i;
}

void Minion::attackDecreasedBy(int i){
    attackVal -= i;
}

int Minion::getAttack(){
    return attackVal;
}

int Minion::getDefense(){
    return defense;
}

CardInfo Minion::getCardInfo() {
    int attack = getAttack();
    int defense = getDefense();
    int activationCost = getActivationCost();

    CardInfo info;
    info.ability_cost = activationCost == 0 ? -1 : activationCost; // some minions do not have activate ability
    info.cost = cost;
    info.desc = description;
    info.leftCorner = to_string(attack);
    info.rightCorner = to_string(defense);
    info.name = name;
    info.type = type;

    return info;
}
