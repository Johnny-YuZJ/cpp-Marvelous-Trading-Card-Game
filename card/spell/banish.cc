#include "banish.h"
#include <string>
#include "../card.h"
#include "../minion/minion.h"
#include "../ritual/ritual.h"
#include <iostream>
using namespace std;

Banish::Banish(shared_ptr<Player> owner)
    : Spell("Banish", 2, "Destroy target minion or ritual", owner){}

void Banish::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target == nullptr){
        cerr << "Banish needs target." << endl;
        return;
    }

    shared_ptr<Minion> m = dynamic_pointer_cast<Minion>(target);
    if (m) {
        m->die();
        return;
    }

    shared_ptr<Ritual> r = dynamic_pointer_cast<Ritual>(target);
    if (r) {
        r->removeThis();
        return;
    }

}
