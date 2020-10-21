#ifndef RITUAL_H_INCLUDED
#define RITUAL_H_INCLUDED

#include <memory>
#include "../card.h"
class Player;
class CardInfo;

class Ritual: public Card, public std::enable_shared_from_this<Ritual>{
    int activationCost;
    int charge;
public:
    Ritual(std::string name, int cost, std::string description, std::shared_ptr<Player> owner, int activationCost, int charge);
    virtual ~Ritual();

    void gainCharge(int i);
    void removeThis();//remove current ritual to used card
    bool canTrigger();
    int getActivationCost();
    int getCharge();
    void chargeDecreasedBy(int i);
    void chargeIncreasedBy(int i);
    void play(std::shared_ptr<Card> target) override;
    CardInfo getCardInfo() override;

};

#endif // RITUAL_H_INCLUDED
