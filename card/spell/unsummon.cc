#include "unsummon.h"
#include <string>
#include <iostream>
#include "../minion/minion.h"
using namespace std;

//Constructor
Unsummon::Unsummon(shared_ptr<Player> owner)
    :Spell("Unsummon", 1, "Return target minion to its owner's hand", owner){}

//return target to handDeck
void Unsummon::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target == nullptr){
        cerr << "Unsummon need target!" << endl;
        return;
    }
    shared_ptr<Minion> m = dynamic_pointer_cast<Minion>(target);
    if (m) {
        m->returnDeck();
        return;
    } else {
        cerr << "Unsummon target only supports minion" << endl;
        return;
    }
}

