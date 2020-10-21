#ifndef __INFO_H__
#define __INFO_H__

#include <string>

struct PlayerInfo {
    int id;
    std::string name;
    int hp;
    int mp;
};

struct CardInfo {
    std::string name;
    std::string type;
    int cost;
    int ability_cost;
    std::string desc;
    std::string leftCorner;
    std::string rightCorner;

};


#endif // !__CARDINFO_H__
