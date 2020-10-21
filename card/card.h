#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <memory>
#include <string>
class Player;
class CardInfo;

class Card{
    std::shared_ptr<Player> owner;

protected:
    int cost;
    std::string type;
    std::string name;
    std::string description;

public:
    Card(std::string type, std::string name, int cost, std::string description, std::shared_ptr<Player> owner); //ctor
    ~Card(); //dtor

    int getCost();
    std::shared_ptr<Player> getOwner();
    virtual bool canPlay(); //check sufficient magic
    virtual void play(std::shared_ptr<Card> target) =0; //check canPlay and decrease magic by its cost
                                        //called when card played from handDeck with a target
    
    // Get CardInfo for display
    virtual CardInfo getCardInfo()=0;
};


#endif // CARD_H_INCLUDED
