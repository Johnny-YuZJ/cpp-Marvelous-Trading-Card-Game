#include "earth_elemental.h"
#include "../../player.h"
#include "../../board.h"
#include <iostream>

using namespace std;

EarthElemental::EarthElemental(shared_ptr<Player> owner): NormalMinion(4, 4, "Earth Elemental", 3, "", owner){}
