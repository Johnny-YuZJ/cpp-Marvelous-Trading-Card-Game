#ifndef player_h
#define player_h

#include <vector>
#include <memory>
#include <string>

class Card;
class Board;
class Ritual;
class NormalMinion;
class Minion;

struct PlayerInfo;
struct CardInfo;

class Player: public std::enable_shared_from_this<Player> {
    int playerId;
    std::string name;
    int hp;
    int magic;
    std::shared_ptr<Board> board; //singleton
    std::shared_ptr<Ritual> ritual; //null if no ritual is played
    std::vector<std::shared_ptr<Card>> deck; //deck to draw cards
    std::vector<std::shared_ptr<Card>> handDeck;
    std::vector<std::shared_ptr<NormalMinion>> graveYard; //implement as a stack
    std::vector<std::shared_ptr<Card>> usedCards;
public:
    Player(int playerId, std::shared_ptr<Board> board);
    void setName(std::string name);
    void setDeck(std::vector<std::shared_ptr<Card>> deck);//first create new player,
                                                          //then create deck of card with owner
                                                          //then call this method
    void setRitual(std::shared_ptr<Ritual> ritual); //place ritual
    void initHandDeck(); // draw 5 cards if deck size >= 5
    
    void gainMagic(); //gain one magic at the start of turn
    void drawCard(); //get the top card from the deck
    void disCard(int i); // discard ith card in hand. only in testing mode.
    void startTurn();
    void endTurn();
    void play(int i); //play the ith card with no target
    void play(int i, std::shared_ptr<Player> p, int t);//play the ith card from the handDeck to
                                                       //the target minion of player p. If t == 0,
                                                       //that means target is the ritual of p.
    void use(int i); //use the ith minion's activated abilities with no target
    void use(int i, std::shared_ptr<Player> p, int t); //use ith minion's activated abilities
                                                       //to the target minion of player p.
                                                       //if  If t == 0, that means target is the ritual of p.
    void removeTheRitual(); //put original ritual to used cards
    void attack(int i, std::shared_ptr<Player> p);// use the ith minion to attack the player p
    void attack(int i, std::shared_ptr<Player> p, int t); // use the ith minion to attack the jth minion of player p
    void useMagic(int i); //decrease magic by i, should be called from card
    void hpDecreasedBy(int i); // deals a damage to a player
    void putToGraveYard(std::shared_ptr<NormalMinion> m);
    void putToHandDeck(std::shared_ptr<Card> c); //if handDeck is full, put to used card
    std::shared_ptr<Card> removeFromHandDeck(std::shared_ptr<Card> c);
    void addToUsedCards(std::shared_ptr<Card> c); //any kind of cards
    std::shared_ptr<NormalMinion> resurrect(); //resurrect the top minion from the graveYard, put to handDeck and return it.
                                              //Do nothing and return NUll if graveYard is empty.
                                              //if handDeck is full, put it to usedCard
    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Ritual> getRitual(); //caller has to check if it is null
    int getMagic(); //return current magic
    int getId(); //return playerId

    bool hasGraveYard();
    
    PlayerInfo getPlayerInfo();
    std::vector<CardInfo> getHandDeckInfo();
    CardInfo getGraveYardInfo();
};
#endif /* player_h */
