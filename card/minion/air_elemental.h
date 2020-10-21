#ifndef air_elemental_h
#define air_elemental_h
#include "normal_minion.h"
#include <memory>

class Player;
class Card;

class AirElemental: public NormalMinion{
public:
    AirElemental(std::shared_ptr<Player> owner);
};

#endif /* air_elemental_h */
