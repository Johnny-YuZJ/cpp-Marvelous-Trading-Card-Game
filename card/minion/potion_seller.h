#ifndef potion_seller_h
#define potion_seller_h

#include "normal_minion.h"
#include "../trigger.h"
#include <memory>

class Player;
class Card;
class Minion;

class PotionSeller: public NormalMinion, public Trigger{
public:
    PotionSeller(std::shared_ptr<Player> owner);
    
    bool hasTrigger() override;
    
    // The player id of the owner of the trigger
    // Used to match with the active player id
    int getPlayerId() override;
    
    // This is used to determine if this trigger from a Ritual card
    // Ritual trigger has to be the last trigger of the player's trigger loop
    bool isRitual() override;
    
    // Register this instance to a specific event
    void registerTrigger() override;
    
    // unregister this instance to a specific event
    void unRegisterTrigger() override;
    
    // Trigger the ability by a minion
    void triggerAbility(std::shared_ptr<Minion> m) override;
    
    // Trigger the ability by a player
    void triggerAbility(std::shared_ptr<Player> p) override;
};

#endif /* potion_seller_h */
