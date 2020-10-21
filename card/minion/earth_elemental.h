#ifndef earth_elemental_h
#define earth_elemental_h
#include "normal_minion.h"
#include <memory>

class Player;
class Card;

class EarthElemental: public NormalMinion{
public:
    EarthElemental(std::shared_ptr<Player> owner);
};
#endif /* earth_elemental_h */
