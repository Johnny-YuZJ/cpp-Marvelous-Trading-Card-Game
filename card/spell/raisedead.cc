#include "raisedead.h"
#include <string>
#include <iostream>
#include "../../player.h"
#include "../minion/normal_minion.h"
using namespace std;

RaiseDead::RaiseDead(shared_ptr<Player> owner)
    : Spell("Raise Dead", 1, "Resurrect the top minion in your graveyard and set its defence to 1", owner){}


void RaiseDead::cast(shared_ptr<Card> target){
    //check if minion is null
    if (target != nullptr){
        cerr << "Raise Dead doesn't need target!" << endl;
        return;
    }
    
    shared_ptr<NormalMinion> temp = getOwner()->resurrect();
    if(temp != nullptr){
        temp->setDefense(1);
    } else {
        cout << "Raise Dead failed" << endl;
    }
}
