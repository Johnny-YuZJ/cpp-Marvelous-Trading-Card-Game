#include "novicefireball.h"
#include "../minion/minion.h"
#include "string"
#include <iostream>
using namespace std;

//Constructor
NoviceFireBall::NoviceFireBall(shared_ptr<Player> owner)
    : Spell("Novice Fire Ball", 1, "Deal 1 damage to target minion", owner){}

void NoviceFireBall::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target == nullptr){
        cerr << "Activate ability needs target!" << endl;
        return;
    }
    
    shared_ptr<Minion> m = dynamic_pointer_cast<Minion>(target);
    if (m) {
        m->defenseDecreasedBy(1);
        return;
    } else {
        cerr << "Activate ability target is not a minion" << endl;
        return;
    }
}

//did nothing
void NoviceFireBall::destroy(){}
