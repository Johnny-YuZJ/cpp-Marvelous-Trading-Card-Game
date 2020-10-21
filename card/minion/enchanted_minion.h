#ifndef enchanted_minion_h
#define enchanted_minion_h
#include "minion.h"
#include <vector>
#include <memory>
#include <string>

class CardInfo;
class Player;
class Enchantment;
class Card;

class EnchantedMinion: public Minion, public std::enable_shared_from_this<EnchantedMinion>{
protected:
    std::shared_ptr<Minion> innerMinion;
    std::shared_ptr<Enchantment> enchantment;
    std::string leftCorner;
    std::string rightCorner;
public:
    // If it is decorating, everything should either be copied from the orignial normal minion or decorated
    EnchantedMinion(std::shared_ptr<Minion> innerMinion, std::shared_ptr<Enchantment> enchantment,
                    int attackVal, int defense, int action, std::string name, int cost,
                 std::string description, std::shared_ptr<Player> owner);
    
    // play does nothing since enchanted minion cannot be in the handdeck
    void play(std::shared_ptr<Card> target) override;
    
    //decorators
    void die() override;
    virtual bool canActivateAbility() override; // override again in Silent
    virtual void restoreAction(int i) override;      // override again in Haste
    int getAction() override;
    void useAction() override;
    int getActivationCost() override;
    void activationCostIncreasedBy(int i) override; // called in magic fatigue ctor
    //activate Ability to the target minion, need to check canActivate
    void activateAbility(std::shared_ptr<Minion> t) override;
    //called by Unsummon
    void returnDeck() override;
    
    virtual void removeTopEnchant() override;    // override in magic fatigue to reset ability cost
    std::vector<CardInfo> getEnchantmentInfo() override;
};

#endif /* enchanted_minion_h */
