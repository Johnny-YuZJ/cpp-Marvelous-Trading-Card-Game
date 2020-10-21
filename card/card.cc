#include "card.h"
#include "../player.h"
#include "../board.h"
using namespace std;

//constructor
Card::Card(string type, string name, int cost, string description, shared_ptr<Player> owner)
: type{type}, name{name}, cost{cost}, description{description}, owner{owner} {}

//destructor
Card::~Card(){}

int Card::getCost(){
    return cost;
}

//get card's owner
shared_ptr<Player> Card::getOwner() {
    return owner;
}

bool Card::canPlay() {
    if(owner->getMagic() >= cost){
        return true;
    }
    else {
        if (getOwner()->getBoard()->isTesting()) {
            return true;
        }
        else {
            return false;
        }
    }
}
