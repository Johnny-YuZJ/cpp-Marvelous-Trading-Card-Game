#ifndef board_h
#define board_h
#include <vector>
#include <memory>

class Minion;
class NormalMinion;
class Player;
class Trigger;
class CardInfo;

enum GameEvent {
    StartTurn,
    EndTurn,
    EnterBoard,
    LeaveBoard
};

class Board {
    int activePlayerId; // used for APNAP order
    bool testMode;
    
    std::vector<std::shared_ptr<Minion>> minionSlot[2];
    
    // Treat as queue, mixed both players, but for each player, the trigger order should be
    // minion 1 to 5 and ritual order is not guarunteed
    std::vector<std::shared_ptr<Trigger>> startTurnTriggers;
    std::vector<std::shared_ptr<Trigger>> endTurnTriggers;
    std::vector<std::shared_ptr<Trigger>> enterBoardTriggers;
    std::vector<std::shared_ptr<Trigger>> leaveBoardTriggers;
    
    // Trigger a specific event by a player or a normal minion in APNAP order
    void trigger(std::shared_ptr<Player> p, GameEvent event);       // StartTurn or EndTurn
    
    // Restores the activePlayer's minions action
    void restoreMinionAction();
    
public:
    Board(bool isTestingMode);
    
    // Set the activePlayerId, trigger StartTurn, and restore active player's minion action
    void startTurn(std::shared_ptr<Player> activePlayer);
    // Trigger EndTurn and unset activePlayerId
    void endTurn(std::shared_ptr<Player> activePlayer);

    // Return true if the testing mode is on, false otherwise
    bool isTesting();
    
    // Return the ith minion from player 1 or 2, i is range from 1 to 5
    std::shared_ptr<Minion> getMinion(int playerId, int i);
    
    // Return a vector of minions from player 1 or 2
    std::vector<std::shared_ptr<Minion>> getMinions(int playerId);
    
    // AOE damage applied to all the minions in APNAP order
    // playerId is the active player
    void aoe(int activePlayerId, int damage);
    
    // Return true if there's availabe minion slot for the player
    bool hasMinionSlot(int playerId);
    
    // Place a NormalMinion to the player's minion slot
    // trigger EnterBoard event
    // attach its triggered ability if it hasTrigger
    void placeMinion(int playerId, std::shared_ptr<NormalMinion> m);
    
    // Replace the old minion with the new minion, used by enchant
    // Use getOwner to get playerId
    // Do not trigger EnterBoard event or register its triggered ability
    // Original goes to usedCard
    void replaceMinion(std::shared_ptr<Minion> original, std::shared_ptr<Minion> updated);
    
    // Place a NormalMinion to the player's minion slot
    // trigger LeaveBoard event
    // detach its triggered ability if it hasTrigger
    std::shared_ptr<NormalMinion> removeMinion(int playerId, std::shared_ptr<NormalMinion> m);
    
    // Attach or detach a trigger to an event so that it will be triggered later or no longer triggered
    void attach(std::shared_ptr<Trigger> trigger, GameEvent event);
    void detach(std::shared_ptr<Trigger> trigger, GameEvent event);

    void trigger(std::shared_ptr<NormalMinion> m, GameEvent event); // EnterBoard or LeaveBoard
    
    std::vector<CardInfo> getPlayerMinionSlotInfo(int playerId);
    std::vector<CardInfo> inspect(int playerId, int i);
};
#endif /* board_h */
