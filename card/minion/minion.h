#ifndef minion_h
#define minion_h
#include "../card.h"
#include <memory>
#include <string>
#include <vector>
class Player;
class CardInfo;

class Minion: public Card {
protected: // Should be private, but being lazy here
    int attackVal;
    int defense;

public:
    Minion(int attackVal, int defense, int action, std::string type, std::string name,
           int cost, std::string description, std::shared_ptr<Player> owner);

    // Check action
    bool canAttack();

    void attack(std::shared_ptr<Player> p);
    void attack(std::shared_ptr<Minion> m);
    void defenseDecreasedBy(int damage); // need to handle death
    void defenseIncreasedBy(int damage);
    void attackIncreasedBy(int i);
    void attackDecreasedBy(int i);
    int getAttack();
    int getDefense();

    //decorators
    virtual void die()=0;
    virtual bool canActivateAbility()=0;
    virtual void restoreAction(int i) =0; // restore action by i
    virtual int getAction() =0;
    virtual void useAction() =0;          // consume 1 action
    virtual void activationCostIncreasedBy(int i) =0;
    virtual int getActivationCost()=0;
    //activate Ability to the target minion, need to check canActivate
    virtual void activateAbility(std::shared_ptr<Minion> t) =0;
    //called by Unsummon
    virtual void returnDeck()=0;

    virtual void removeTopEnchant()=0;

    // Get the card info of itself. However, defense and attack should count enchantment
    CardInfo getCardInfo() override;
    // Follow the decorator pattern to get a vector of enchantment from inner-most to outer-most
    virtual std::vector<CardInfo> getEnchantmentInfo()=0;
};
#endif /* minion_h */
