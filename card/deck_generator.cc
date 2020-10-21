 #include "deck_generator.h"
#include "spell/banish.h"
#include "spell/blizzard.h"
#include "spell/unsummon.h"
#include "spell/recharge.h"
#include "spell/disenchant.h"
#include "spell/raisedead.h"
#include "minion/air_elemental.h"
#include "minion/earth_elemental.h"
#include "minion/bone_golem.h"
#include "ritual/darkritual.h"
#include "ritual/auraofpower.h"
#include "ritual/standstill.h"
#include "minion/fire_elemental.h"
#include "minion/potion_seller.h"
#include "minion/novice_pyromancer.h"
#include "minion/apprentice_summoner.h"
#include "minion/master_summoner.h"
#include "enchantment/giant_strength.h"
#include "enchantment/enrage.h"
#include "enchantment/haste.h"
#include "enchantment/magic_fatigue.h"
#include "enchantment/silence.h"
#include "../player.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <ctime>
#include <cstdlib>

using namespace std;

DeckGenerator::DeckGenerator(){
    shuffleTime = 1;
}

void DeckGenerator::swap(vector<shared_ptr<Card>> &vec, int a, int b) {
    shared_ptr<Card> tmp = vec[a];
    vec[a] = vec[b];
    vec[b] = tmp;
}

void DeckGenerator::shuffle(vector<shared_ptr<Card>> &deck) {
    srand(time(NULL));
    if (deck.size() == 0) return;
    for (int j = 0; j < shuffleTime; j++) {
        for (int i = 1; i < deck.size(); ++i) {
            int target = rand() % (i + 1);
            swap(deck, i, target);
        }
    }
}


vector<shared_ptr<Card>> DeckGenerator::generate(string filename, shared_ptr<Player> p, bool ifNotShuffle) {
    ifstream cardFile(filename);
    vector<shared_ptr<Card>> deck;
    if (cardFile.is_open()) {
        string cardName;
        while (getline(cardFile, cardName)) {
            // Spell
            if (cardName == "Banish") {
                deck.push_back(make_shared<Banish>(p));
            }
            if (cardName == "Blizzard") {
                deck.push_back(make_shared<Blizzard>(p));
            }
            if (cardName == "Unsummon") {
                deck.push_back(make_shared<Unsummon>(p));
            }
            if (cardName == "Recharge") {
                deck.push_back(make_shared<Recharge>(p));
            }
            if (cardName == "Disenchant") {
                deck.push_back(make_shared<Disenchant>(p));
            }
            if (cardName == "Raise Dead") {
                deck.push_back(make_shared<RaiseDead>(p));
            }
            
            // Minion
            if (cardName == "Air Elemental") {
                deck.push_back(make_shared<AirElemental>(p));
            }
            if (cardName == "Earth Elemental") {
                deck.push_back(make_shared<EarthElemental>(p));
            }
            if (cardName == "Bone Golem") {
                deck.push_back(make_shared<BoneGolem>(p));
            }
            if (cardName == "Fire Elemental") {
                deck.push_back(make_shared<FireElemental>(p));
            }
            if (cardName == "Potion Seller") {
                deck.push_back(make_shared<PotionSeller>(p));
            }
            if (cardName == "Novice Pyromancer") {
                deck.push_back(make_shared<NovicePyromancer>(p));
            }
            if (cardName == "Apprentice Summoner") {
                deck.push_back(make_shared<ApprenticeSummoner>(p));
            }
            if (cardName == "Master Summoner") {
                deck.push_back(make_shared<MasterSummoner>(p));
            }
            if (cardName == "Giant Strength") {
                deck.push_back(make_shared<GiantStrength>(p));
            }
            if (cardName == "Enrage") {
                deck.push_back(make_shared<Enrage>(p));
            }
            if (cardName == "Haste") {
                deck.push_back(make_shared<Haste>(p));
            }
            if (cardName == "Magic Fatigue") {
                deck.push_back(make_shared<MagicFatigue>(p));
            }
            if (cardName == "Silence") {
                deck.push_back(make_shared<Silence>(p));            }
            //Ritual
            if (cardName == "Dark Ritual") {
                deck.push_back(make_shared<DarkRitual>(p));
            }
            if (cardName == "Aura of Power") {
                deck.push_back(make_shared<AuraOfPower>(p));
            }
            if (cardName == "Standstill") {
                deck.push_back(make_shared<Standstill>(p));
            }
        }
    } else {
        throw "Cannot open file:" + filename;
    }

    if (!ifNotShuffle) {
        shuffle(deck);
        shuffleTime++;
    }
    return deck;
}
