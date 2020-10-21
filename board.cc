#include "board.h"
#include "player.h"
#include "card/minion/minion.h"
#include "card/minion/normal_minion.h"
#include "card/trigger.h"
#include "display/info.h"
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board(bool isTestingMode) {
    vector<shared_ptr<Minion>> slot1;
    vector<shared_ptr<Minion>> slot2;
    minionSlot[0] = slot1;
    minionSlot[1] = slot2;
    testMode = isTestingMode;
    activePlayerId = -1;
}

void Board::startTurn(std::shared_ptr<Player> activePlayer){
    activePlayerId = activePlayer->getId();
    trigger(activePlayer, GameEvent::StartTurn);
    restoreMinionAction();
}

void Board::endTurn(std::shared_ptr<Player> activePlayer){
    trigger(activePlayer, GameEvent::EndTurn);
    activePlayerId = -1;
}

bool Board::isTesting() {
    return testMode;
}

void Board::restoreMinionAction() {
    auto minions = getMinions(activePlayerId);
    for (auto& minion : minions) {
        minion->restoreAction(0); // start with no enchant
    }
}

shared_ptr<Minion> Board::getMinion(int playerId, int i){
    if (i < 1 || i > 5) {
        cerr << "Please enter a number between 1 to 5" << endl;
        return nullptr;
    }
    if (i - 1 >= minionSlot[playerId - 1].size()) {
        cerr << "Minion not exist" << endl;
        return nullptr;
    }
    return minionSlot[playerId - 1][i - 1];
}

vector<std::shared_ptr<Minion>> Board::getMinions(int playerId){
    return minionSlot[playerId - 1];
}

void Board::aoe(int activePlayerId, int damage){
    int index = activePlayerId - 1; // either 0 or 1
    auto activePlayerVector = minionSlot[index];
    auto nonActivePlayerVector = minionSlot[1 - index];
    
    // Active Player
    for (auto& minion : activePlayerVector) {
        minion->defenseDecreasedBy(damage);
    }
    // Non-Active Player
    for (auto& minion : nonActivePlayerVector) {
        minion->defenseDecreasedBy(damage);
    }
}

bool Board::hasMinionSlot(int playerId){
    return minionSlot[playerId - 1].size() < 5;
}

void Board::placeMinion(int playerId, shared_ptr<NormalMinion> m){
    if (hasMinionSlot(playerId)) {
        minionSlot[playerId - 1].push_back(m);
        trigger(m, GameEvent::EnterBoard);
        
        if (m->hasTrigger()) {
            shared_ptr<Trigger> trigger = dynamic_pointer_cast<Trigger>(m);
            if (trigger) {
                trigger->registerTrigger();
            } else {
                cerr << "Failed to cast Normal Minion into Trigger" << endl;
            }
        }
    } else {
        cerr << "minion slot is full" << endl;
    }
}

void Board::replaceMinion(shared_ptr<Minion> original, shared_ptr<Minion> updated){
    int playerId = original->getOwner()->getId();
    auto minions = &minionSlot[playerId - 1];
    auto it = find(minions->begin(), minions->end(), original);
    if (it != minions->end()) {
        *it = updated;
        original->getOwner()->addToUsedCards(original);
    } else {
        cerr << "Failed to replace minion from the board" << endl;
    }
}

shared_ptr<NormalMinion> Board::removeMinion(int playerId, shared_ptr<NormalMinion> m){
    auto minions = &minionSlot[playerId - 1];
    auto it = find(minions->begin(), minions->end(), m);
    if (it != minions->end()) {
        minions->erase(it);
        if (m->hasTrigger()) {
            shared_ptr<Trigger> trigger = dynamic_pointer_cast<Trigger>(m);
            if (trigger) {
                trigger->unRegisterTrigger();
            } else {
                cerr << "Failed to cast Normal Minion into Trigger" << endl;
            }
        }
        trigger(m, GameEvent::LeaveBoard);
    } else {
        cerr << "Failed to remove minion from the board" << endl;
    }
    return m;
}

// StartTurn or EndTurn
void Board::trigger(shared_ptr<Player> p, GameEvent event){
    int index = activePlayerId - 1; // either 0 or 1
    vector<shared_ptr<Trigger>> eventTriggers;
    
    // determine which event is triggered
    switch (event) {
        case GameEvent::StartTurn:
            eventTriggers = startTurnTriggers;
            break;
        case GameEvent::EndTurn:
            eventTriggers = endTurnTriggers;
            break;
        default:
            cerr << "Invalid trigger event for player" << endl;
            break;
    }
    
    // Active Player Minion trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() == activePlayerId && !eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(p);
        }
    }
    // Active Player Ritual trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() == activePlayerId && eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(p);
        }
    }
    
    // Non-Active Player Minion trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() - 1 == 1 - index && !eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(p);
        }
    }
    // Non-Active Player Ritual trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() - 1 == 1 - index && eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(p);
        }
    }
}

// EnterBoard or LeaveBoard
void Board::trigger(shared_ptr<NormalMinion> m, GameEvent event){
    int index = activePlayerId - 1; // either 0 or 1
    vector<shared_ptr<Trigger>> eventTriggers;
    
    // determine which event is triggered
    switch (event) {
        case GameEvent::EnterBoard:
            eventTriggers = enterBoardTriggers;
            break;
        case GameEvent::LeaveBoard:
            eventTriggers = leaveBoardTriggers;
            break;
        default:
            cerr << "Invalid trigger event for minion" << endl;
            break;
    }
    
    // Active Player Minion trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() == activePlayerId && !eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(m);
        }
    }
    // Active Player Ritual trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() == activePlayerId && eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(m);
        }
    }
    
    // Non-Active Player Minion trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() - 1 == 1 - index && !eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(m);
        }
    }
    // Non-Active Player Ritual trigger
    for (auto& eventTrigger : eventTriggers) {
        if (eventTrigger->getPlayerId() - 1 == 1 - index && eventTrigger->isRitual()) {
            eventTrigger->triggerAbility(m);
        }
    }
}

void Board::attach(shared_ptr<Trigger> trigger, GameEvent event){
    switch (event) {
        case GameEvent::StartTurn:
            startTurnTriggers.push_back(trigger);
            break;
        case GameEvent::EndTurn:
            endTurnTriggers.push_back(trigger);
            break;
        case GameEvent::EnterBoard:
            enterBoardTriggers.push_back(trigger);
            break;
        case GameEvent::LeaveBoard:
            leaveBoardTriggers.push_back(trigger);
            break;
        default:
            break;
    }
}

void Board::detach(shared_ptr<Trigger> trigger, GameEvent event){
    vector<shared_ptr<Trigger>> *eventTriggers;
    
    // determine which event is triggered
    switch (event) {
        case GameEvent::StartTurn:
            eventTriggers = &startTurnTriggers;
            break;
        case GameEvent::EndTurn:
            eventTriggers = &endTurnTriggers;
            break;
        case GameEvent::EnterBoard:
            eventTriggers = &enterBoardTriggers;
            break;
        case GameEvent::LeaveBoard:
            eventTriggers = &leaveBoardTriggers;
            break;
        default:
            break;
    }
    
    // erase from the triggers
    auto it = find(eventTriggers->begin(), eventTriggers->end(), trigger);
    if (it != eventTriggers->end()) {
        eventTriggers->erase(it);
    } else {
        cerr << "Failed to detach trigger from the board" << endl;
    }
}

vector<CardInfo> Board::getPlayerMinionSlotInfo(int playerId){
    vector<CardInfo> minionSlotInfo;
    for (auto& minion : minionSlot[playerId - 1]) {
        minionSlotInfo.push_back(minion->getCardInfo());
    }
    
    return minionSlotInfo;
}

vector<CardInfo> Board::inspect(int playerId, int i){
    shared_ptr<Minion> m = getMinion(playerId, i);
    if(m == nullptr) {
        string error = "Inspect failed";
        throw error;
    }
    vector<CardInfo> enchantmentInfo = m->getEnchantmentInfo();
    CardInfo minionInfo = m->getCardInfo();
    enchantmentInfo.insert(enchantmentInfo.begin(), minionInfo);
    return enchantmentInfo;
}
