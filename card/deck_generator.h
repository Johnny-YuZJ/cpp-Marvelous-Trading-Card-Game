#ifndef __DECK_GENERATOR_H__
#define __DECK_GENERATOR_H__
#include <string>
#include <vector>
#include <memory>

class Card;
class Player;

class DeckGenerator {
private:
    int shuffleTime;
    void swap(std::vector<std::shared_ptr<Card>> &vec, int a, int b);
    void shuffle(std::vector<std::shared_ptr<Card>> &deck);
    
public:
    DeckGenerator();
    std::vector<std::shared_ptr<Card>> generate(std::string filename, std::shared_ptr<Player> p, bool ifNotShuffle);
};
#endif
