#ifndef normal_minion_h
#define normal_minion_h
#include <string>
#include <memory>
#include <vector>
#include "minion.h"

class CardInfo;
class Player;

class NormalMinion: public Minion, public std::enable_shared_from_this<NormalMinion>{
private:
    int action;

public:
    NormalMinion(int attackVal, int defense, std::string name, int cost,
                 std::string description, std::shared_ptr<Player> owner);
    
    void setDefense(int i);
    
    bool canPlay() override; // need to check cost and board slot availability
    void play(std::shared_ptr<Card> target) override;
    
    virtual bool hasTrigger();       // default false, override it if it has
    virtual void die() override; // default move to graveyard, remove from board
    
    virtual bool canActivateAbility() override; // default to false,
                                        // override to true if the minion has an activated ability
    void restoreAction(int i) override;
    int getAction() override;
    void useAction() override;
    virtual void activationCostIncreasedBy(int i) override; // default does nothing, override it if it has ability
    virtual int getActivationCost() override; // default return 0, override it if it has activated ability
    virtual void activateAbility(std::shared_ptr<Minion> t) override; // default does nothing, override it if it has
    
    void returnDeck() override; // default call player putToHandDeck, and board removeMinion
    void removeTopEnchant() override; // does nothing
    std::vector<CardInfo> getEnchantmentInfo() override; // return an empty vector
};
#endif /* normal_minion_h */
