#ifndef trigger_h
#define trigger_h
#include <memory>

class Minion;
class Player;

// This interface provides the necessary methods for the Trigger mechanism
// The class needs to implement those methods
class Trigger{
public:
    // The player id of the owner of the trigger
    // Used to match with the active player id
    virtual int getPlayerId()=0;
    
    // This is used to determine if this trigger from a Ritual card
    // Ritual trigger has to be the last trigger of the player's trigger loop
    virtual bool isRitual()=0;
    
    // Register this instance to a specific event
    virtual void registerTrigger()=0;
    
    // unregister this instance to a specific event
    virtual void unRegisterTrigger()=0;
    
    // Trigger the ability by a minion
    virtual void triggerAbility(std::shared_ptr<Minion> m)=0;
    
    // Trigger the ability by a player
    virtual void triggerAbility(std::shared_ptr<Player> p)=0;
};
#endif /* trigger_h */
