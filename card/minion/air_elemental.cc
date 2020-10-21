#include "air_elemental.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

AirElemental::AirElemental(shared_ptr<Player> owner): NormalMinion(1, 1, "Air Elemental", 0, "", owner){}
