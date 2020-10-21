#include "player.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "board.h"
#include "card/ritual/ritual.h"
#include "card/card.h"
#include "card/minion/normal_minion.h"
#include "display/info.h"
#include "card/trigger.h"
using namespace std;

//Constructor
Player::Player(int playerId, shared_ptr<Board> board)
    :playerId{playerId}, hp{20}, magic{3}, board{board}, ritual{nullptr}{}

//set player's name
void Player::setName(string name){
    this->name = name;
}

//set deck
void Player::setDeck(vector<shared_ptr<Card>> deck){
    this->deck = deck;
}

//set ritual
void Player::setRitual(std::shared_ptr<Ritual> ritual){
    this->ritual = ritual;
    shared_ptr<Trigger> t = dynamic_pointer_cast<Trigger>(ritual);
    t->registerTrigger();
}

void Player::initHandDeck(){
    int count = 5;
    while (count > 0 && deck.size() > 0){
        drawCard();
        count--;
    }
}

//gain one magic at the start of turn
void Player::gainMagic(){
    ++magic;
}

//remove the card
void Player::removeTheRitual(){
    if(ritual != nullptr){
        addToUsedCards(ritual);
        shared_ptr<Trigger> tr = dynamic_pointer_cast<Trigger>(ritual);
        tr->unRegisterTrigger();
        ritual = nullptr;
    }
}

//get the top card from the deck
void Player::drawCard(){
    if(this->deck.size() <= 0) {
        cout << "No card in deck!" << endl;
        return;
    } else if (this->handDeck.size() >= 5){
        cout << "Hand is full!" <<endl;
        return;
    } else {
        this->handDeck.push_back(this->deck.front());
        this->deck.erase(deck.begin());
    }
}

void Player::disCard(int i) {
    if (i < 1 || i > 5) {
        cerr << "Please enter a number between 1 to 5" << endl;
        return;
    }
    if (i - 1 >= handDeck.size()) {
        cerr << "Card not exist" << endl;
        return;
    }
    addToUsedCards(handDeck[i - 1]);
    shared_ptr<Card> removedCard = removeFromHandDeck(handDeck[i - 1]);
    shared_ptr<NormalMinion> c = dynamic_pointer_cast<NormalMinion> (removedCard);
    if (c) {
        getBoard()->trigger(c, LeaveBoard);
    }

}

//start turn trigger
void Player::startTurn(){
    cout << name + "'s turn" << endl;
    gainMagic();
    drawCard();
    board->startTurn(shared_from_this());
}

//end turn trigger
void Player::endTurn(){
    board->endTurn(shared_from_this());
}

//play the ith card with no target
void Player::play(int i){
    if (i < 1 || i > 5) {
        cerr << "Please enter a number between 1 to 5" << endl;
        return;
    }
    if (i - 1 >= handDeck.size()) {
        cerr << "Card not exist" << endl;
        return;
    }
    this->handDeck[i-1]->play(nullptr);
}

//play the ith card from the handDeck to
void Player::play(int i, shared_ptr<Player> p, int t){
    if (i < 1 || i > 5) {
        cerr << "Please enter a number between 1 to 5" << endl;
        return;
    }
    if (i - 1 >= handDeck.size()) {
        cerr << "Card not exist" << endl;
        return;
    }
    
    if(t == 0){
        this->handDeck[i-1]->play(p->ritual);
    } else {
        this->handDeck[i-1]->play(board->getMinion(p->getId(), t));
    }
}

//use the ith minion's activated abilities with no target
void Player::use(int i){
    board->getMinion(getId(), i)->activateAbility(nullptr);
}

//use ith minion's activated abilities to the target minion of player p.
//if  If t == 0, that means target is the ritual of p.
void Player::use(int i, shared_ptr<Player> p, int t){
    board->getMinion(getId(), i)->activateAbility(board->getMinion(p->getId(), t));
}

// use the ith minion to attack the player p
void Player::attack(int i, shared_ptr<Player> p){
    board->getMinion(getId(), i)->attack(p);
}

// use the ith minion to attack the jth minion of player p
void Player::attack(int i, shared_ptr<Player> p, int t){
    board->getMinion(getId(), i)->attack(board->getMinion(p->getId(), t));
}

//decrease magic by i, should be called from card
void Player::useMagic(int i){
    this->magic-=i;
    // Assume magic won't get below zero
    if (magic < 0) {
        magic = 0;
    }
}

void Player::hpDecreasedBy(int i){
    string loserMessage = name + " died! Game Over!";
    hp -= i;
    if(hp <= 0){
        throw loserMessage;
    }
}

void Player::putToGraveYard(shared_ptr<NormalMinion> m){
    graveYard.push_back(m);
}

//if handDeck is full, put to used card
void Player::putToHandDeck(shared_ptr<Card> c){
    if (this->handDeck.size() >= 5){
        this->usedCards.push_back(c);
    } else {
        this->handDeck.push_back(c);
    }
}

shared_ptr<Card> Player::removeFromHandDeck(shared_ptr<Card> c){
    auto it = find(handDeck.begin(), handDeck.end(), c);
    if (it != handDeck.end()) {
        handDeck.erase(it);
    } else {
        cerr << "Failed to remove card from the hand deck" << endl;
    }
    return c;
}

void Player::addToUsedCards(shared_ptr<Card> c){
    this->usedCards.push_back(c);
}

//resurrect the top minion from the graveYard, put to handDeck and return it.
//Do nothing and return NUll if graveYard is empty. if handDeck is full, put it to usedCard
shared_ptr<NormalMinion> Player::resurrect(){
    if(this->graveYard.size() == 0){
        cout << "GraveYard is empty!" << endl;
        return nullptr;
    } else if (!getBoard()->hasMinionSlot(getId())){
        this->usedCards.push_back(graveYard.back());
        this->graveYard.pop_back();
        cout<< "Minion slot is full! Minion goes to used cards"<<endl;
        return nullptr;
    } else {
        auto minion = graveYard.back();
        getBoard()->placeMinion(getId(), minion);
        this->graveYard.pop_back();
        return minion;
    }
}

shared_ptr<Board> Player::getBoard(){
    return this->board;
}

//caller has to check if it is null
shared_ptr<Ritual> Player::getRitual(){
    return this->ritual;
}

//return current magic
int Player::getMagic(){
    return this->magic;
}

//return playerId
int Player::getId(){
    return this->playerId;
}

bool Player::hasGraveYard() {
    return graveYard.size() > 0;
}

PlayerInfo Player::getPlayerInfo(){
    PlayerInfo info;
    info.hp = hp;
    info.id = playerId;
    info.mp = magic;
    info.name = name;

    return info;
}

vector<CardInfo> Player::getHandDeckInfo(){
    vector<CardInfo> handDeckInfo;
    for (auto& card : handDeck) {
        handDeckInfo.push_back(card->getCardInfo());
    }
    
    return handDeckInfo;
}

CardInfo Player::getGraveYardInfo(){
    return graveYard.back()->getCardInfo();
}
