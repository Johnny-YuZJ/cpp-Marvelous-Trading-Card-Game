#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include "info.h"
#include "ascii_graphics.h"
#include "window.h"
#include "display.h"

using namespace std;

GameDisplay::GameDisplay(bool graphic) : graphic{ graphic } {
    if (graphic) {
        cout << "graphic on" << endl;
        w = make_shared<Xwindow>(1200, 1000);
    }
    else {
        cout << "graphic off" << endl;
        w = nullptr;
    }
    h = nullptr;
    insM = nullptr;
    reset();
}

void GameDisplay::reset() {
    minionP1.clear();
    minionP2.clear();
    
    ritualP1 = CardInfo{"", "", 0, 0, "", "", ""};
    ritualP2 = CardInfo{"", "", 0, 0, "", "", ""};
    graveyardP1 = CardInfo{"", "", 0, 0, "", "", ""};
    graveyardP2 = CardInfo{"", "", 0, 0, "", "", ""};
}

void GameDisplay::setPlayer(PlayerInfo pi, int player) {
    if (player == 1) {
        player1 = pi;
    }
    else if (player == 2) {
        player2 = pi;
    }
    else {
        cerr << "Invalid player id. Please input again." << endl;
    }
}

void GameDisplay::setRitual(CardInfo ci, int player) {
    if (player == 1) {
        ritualP1 = ci;
    }
    else if (player == 2) {
        ritualP2 = ci;
    }
    else {
        cerr << "Invalid player id. Please input again." << endl;
    }
}

void GameDisplay::setGraveyard(CardInfo ci, int player) {
    if (player == 1) {
        graveyardP1 = ci;
    }
    else if (player == 2) {
        graveyardP2 = ci;
    }
    else {
        cerr << "Invalid player id. Please input again." << endl;
    }
}

void GameDisplay::setMinion(std::vector<CardInfo> ci, int player) {
    if (player == 1) {
        minionP1 = ci;
    }
    else if (player == 2) {
        minionP2 = ci;
    }
    else {
        cerr << "Invalid player id. Please input again." << endl;
    }
}

void GameDisplay::boardDisplay() {
    boardTD();
    if (graphic) boardGD();
}

void GameDisplay::handDisplay(vector<CardInfo> hand) {
    handTD(hand);
    if (graphic) handGD(hand);
}

void GameDisplay::inspectMinion(vector<CardInfo> m) {
    inspectTD(m);
    if (graphic) inspectGD(m);
}

card_template_t GameDisplay::display_minion(CardInfo ci) {
    card_template_t t;
    if (ci.ability_cost >= 0) {
        t = display_minion_activated_ability(ci.name, ci.cost,
            ci.leftCorner, ci.rightCorner, ci.ability_cost, ci.desc);
    }
    else {
        t = display_minion_triggered_ability(ci.name, ci.cost,
            ci.leftCorner, ci.rightCorner, ci.desc);
    }
    return t;
}

card_template_t GameDisplay::display_enchant(CardInfo ci) {
    card_template_t t;
    if ((ci.leftCorner == "") && (ci.rightCorner == "")) {
        t = display_enchantment(ci.name, ci.cost, ci.desc);
    }
    else {
        t = display_enchantment_attack_defence(ci.name, ci.cost, ci.desc,
            ci.leftCorner, ci.rightCorner);
    }
    return t;
}

void GameDisplay::boardTD() {
    card_template_t p1TD = display_player_card(player1.id, player1.name, player1.hp, player1.mp);
    card_template_t p2TD = display_player_card(player2.id, player2.name, player2.hp, player2.mp);

    card_template_t r1TD;
    card_template_t r2TD;
    card_template_t g1TD;
    card_template_t g2TD;

    if (ritualP1.type == "") {
        r1TD = CARD_TEMPLATE_BORDER;
    }
    else {
        r1TD = display_ritual(ritualP1.name, ritualP1.cost, ritualP1.ability_cost,
            ritualP1.desc, ritualP1.rightCorner);
    }
    if (ritualP2.type == "") {
        r2TD = CARD_TEMPLATE_BORDER;
    }
    else {
        r2TD = display_ritual(ritualP2.name, ritualP2.cost, ritualP2.ability_cost,
            ritualP2.desc, ritualP2.rightCorner);
    }

    if (graveyardP1.type == "") {
        g1TD = CARD_TEMPLATE_BORDER;
    }
    else {
        g1TD = display_minion(graveyardP1);
    }
    if (graveyardP2.type == "") {
        g2TD = CARD_TEMPLATE_BORDER;
    }
    else {
        g2TD = display_minion(graveyardP2);
    }

    vector<card_template_t> m1TD;
    vector<card_template_t> m2TD;

    for (int i = 0; i < 5; ++i) {
        if (i < minionP1.size()) {
            m1TD.push_back(display_minion(minionP1[i]));
        }
        else {
            m1TD.push_back(CARD_TEMPLATE_BORDER);
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (i < minionP2.size()) {
            m2TD.push_back(display_minion(minionP2[i]));
        }
        else {
            m2TD.push_back(CARD_TEMPLATE_BORDER);
        }
    }
    
    for (int i = 0; i < 11; ++i) {
        cout << r1TD[i] << CARD_TEMPLATE_EMPTY[i] << p1TD[i]
            << CARD_TEMPLATE_EMPTY[i] << g1TD[i] << endl;
    }
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << m1TD[j][i];
        }
        cout << endl;
    }
    for (int i = 0; i < 10; ++i) {
        cout << CENTRE_GRAPHIC[i] << endl;
    }
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << m2TD[j][i];
        }
        cout << endl;
    }
    for (int i = 0; i < 11; ++i) {
        cout << r2TD[i] << CARD_TEMPLATE_EMPTY[i] << p2TD[i]
            << CARD_TEMPLATE_EMPTY[i] << g2TD[i] << endl;
    }
}

void GameDisplay::handTD(vector<CardInfo> hand) {
    vector<card_template_t> hTD;

    for (int i = 0; i < 5; ++i) {
        if (i < hand.size()) {
            if (hand[i].type == "Spell") {
                hTD.push_back(display_spell(hand[i].name, hand[i].cost, hand[i].desc));
            }
            else if (hand[i].type == "Ritual") {
                hTD.push_back(display_ritual(hand[i].name, hand[i].cost,
                    hand[i].ability_cost, hand[i].desc, hand[i].rightCorner));
            }
            else if (hand[i].type == "Enchantment") {
                hTD.push_back(display_enchant(hand[i]));
            }
            else {
                hTD.push_back(display_minion(hand[i]));
            }
        }
        else {
            hTD.push_back(CARD_TEMPLATE_BORDER);
        }
    }
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << hTD[j][i];
        }
        cout << endl;
    }
}

void GameDisplay::inspectTD(std::vector<CardInfo> m) {
    card_template_t minion;
    vector<card_template_t> enchant;

    minion = display_minion(m[0]);

    for (int i = 1; i < m.size(); ++i) {
        enchant.push_back(display_enchant(m[i]));
    }

    for (int i = 0; i < 11; ++i) {
        cout << minion[i] << endl;
    }

    if (enchant.size() > 0) {
        int rest = enchant.size();
        while (rest > 0) {
            for (int i = 0; i < 11; ++i) {
                if (rest >= 5) {
                    for (int j = 0; j < 5; ++j) {
                        cout << enchant[j][i];
                    }
                    cout << endl;
                }
                else {
                    for (int j = 0; j < rest; ++j) {
                        cout << enchant[j][i];
                    }
                    cout << endl;
                }
            }
            rest -= 5;
        }
    }
}

void GameDisplay::boardGD() {
    drawBasic();
    drawPlayer();
    drawBoard();
}

void GameDisplay::handGD(std::vector<CardInfo> hand) {
    if (h == nullptr) {
        h = make_shared<Xwindow>(1200, 240);
    }
    drawHand(hand);
}

void GameDisplay::inspectGD(std::vector<CardInfo> m) {
    // draw the minion
    if (insM == nullptr) {
        insM = make_shared<Xwindow>(1200, 720);
    }
    insM->fillRectangle(0, 0, 1200, 720, Xwindow::Black);
    insM->fillRectangle(500, 20, 200, 180, Xwindow::Orange);
    insM->fillRectangle(505, 25, 190, 170, Xwindow::Brown);
    drawATK(insM, 510, 135, m[0].leftCorner);
    drawHP(insM, 635, 135, m[0].rightCorner);
    ostringstream oss;
    oss << m[0].cost;
    drawMP(insM, 635, 35, oss.str());
    insM->drawString(580, 40, m[0].name, Xwindow::White);
    insM->drawString(580, 60, "Minion", Xwindow::Black);
    // draw the enchantments
    if (m.size() > 0) {
        int rest = (m.size() - 1);
        while (rest > 0) {
            int line = 0;
            int numEnchant = 1;
            if (rest >= 5) {
                for (int i = 0; i < 5; ++i) {
                    insM->fillRectangle(60 + (i * 220), 240 + (line * 220), 200, 180, Xwindow::Green);
                    if ((m[numEnchant].leftCorner == "") && (m[numEnchant].rightCorner == "")) {
                        insM->fillRectangle(65 + (i * 220), 245 + (line * 220), 190, 170, Xwindow::Brown);
                        ostringstream oss;
                        oss << m[numEnchant].cost;
                        drawMP(insM, 195 + (i * 220), 255 + (line * 220), oss.str());
                        insM->drawString(140 + (i * 220), 265 + (line * 220), m[numEnchant].name, Xwindow::White);
                        insM->drawString(140 + (i * 220), 285 + (line * 220), "Enchantment", Xwindow::Black);
                    }
                    else {
                        drawMinion(insM, 60 + (i * 220), 240 + (line * 220), m[numEnchant]);
                    }
                    numEnchant--;
                }
            }
            else {
                for (int i = 0; i < rest; ++i) {
                    insM->fillRectangle(60 + (i * 220), 240 + (line * 220), 200, 180, Xwindow::Green);
                    if ((m[numEnchant].leftCorner == "") && (m[numEnchant].rightCorner == "")) {
                        insM->fillRectangle(65 + (i * 220), 245 + (line * 220), 190, 170, Xwindow::Brown);
                        ostringstream oss;
                        oss << m[numEnchant].cost;
                        drawMP(insM, 195 + (i * 220), 255 + (line * 220), oss.str());
                        insM->drawString(140 + (i * 220), 265 + (line * 220), m[numEnchant].name, Xwindow::White);
                        insM->drawString(140 + (i * 220), 285 + (line * 220), "Enchantment", Xwindow::Black);
                    }
                    else {
                        drawMinion(insM, 60 + (i * 220), 240 + (line * 220), m[numEnchant]);
                    }
                    numEnchant++;
                }
            }
            rest -= 5;
            line++;
        }
    }
}


void GameDisplay::drawBasic() {
    w->fillRectangle(0, 0, 1200, 1000, Xwindow::Black);
    w->fillRectangle(0, 440, 1200, 120, Xwindow::White);
    w->drawString(580, 500, "Sorcery", Xwindow::Blue);
}

void GameDisplay::drawHP(shared_ptr<Xwindow> w, int x, int y, string hp) {
    w->fillRectangle(x, y + 10, 55, 20, Xwindow::Red);
    w->fillRectangle(x + 5, y + 5, 20, 35, Xwindow::Red);
    w->fillRectangle(x + 30, y + 5, 20, 35, Xwindow::Red);
    w->fillRectangle(x + 10, y, 10, 45, Xwindow::Red);
    w->fillRectangle(x + 35, y, 10, 45, Xwindow::Red);
    w->fillRectangle(x + 15, y + 30, 25, 20, Xwindow::Red);
    w->fillRectangle(x + 22, y + 50, 10, 5, Xwindow::Red);
    w->drawString(x + 25, y + 28, hp, Xwindow::White);
}

void GameDisplay::drawMP(shared_ptr<Xwindow> w, int x, int y, string mp) {
    w->fillRectangle(x + 15, y, 25, 45, Xwindow::Blue);
    w->fillRectangle(x + 10, y + 6, 35, 33, Xwindow::Blue);
    w->fillRectangle(x + 5, y + 12, 45, 21, Xwindow::Blue);
    w->fillRectangle(x, y + 18, 55, 9, Xwindow::Blue);
    w->drawString(x + 25, y + 24, mp, Xwindow::White);
}

void GameDisplay::drawATK(shared_ptr<Xwindow> w, int x, int y, string atk) {
    w->fillRectangle(x, y + 45, 55, 7, Xwindow::Orange);
    w->fillRectangle(x + 5, y + 37, 45, 8, Xwindow::Orange);
    w->fillRectangle(x + 10, y + 29, 35, 8, Xwindow::Orange);
    w->fillRectangle(x + 15, y + 21, 25, 8, Xwindow::Orange);
    w->fillRectangle(x + 20, y + 13, 15, 8, Xwindow::Orange);
    w->fillRectangle(x + 25, y + 5, 5, 8, Xwindow::Orange);
    w->drawString(x + 25, y + 30, atk, Xwindow::White);
}

void GameDisplay::drawACost(shared_ptr<Xwindow> w, int x, int y, string abilityCost) {
    w->fillRectangle(x, y + 25, 55, 5, Xwindow::Cyan);
    w->fillRectangle(x + 5, y + 20, 45, 15, Xwindow::Cyan);
    w->fillRectangle(x + 10, y + 15, 35, 25, Xwindow::Cyan);
    w->fillRectangle(x + 15, y + 10, 25, 35, Xwindow::Cyan);
    w->fillRectangle(x + 20, y + 5, 15, 45, Xwindow::Cyan);
    w->fillRectangle(x + 25, y, 5, 55, Xwindow::Cyan);
    w->drawString(x + 25, y + 26, abilityCost, Xwindow::Black);
}

void GameDisplay::drawDesc(shared_ptr<Xwindow> w, int x, int y, string desc) {
    int i = 0;
    string s;
    int l = 0;
    while(desc.length() - i > 24) {
        s = desc.substr(i, i + 24);
        w->drawString(x + 15 - l, l * 12 + y + 70, s, Xwindow::White);
        ++l;
        i += 24;
    }
    s = desc.substr(i, desc.length() - i);
    w->drawString(x + 15, l * 15 + y + 65, s, Xwindow::White);
}

void GameDisplay::drawMinion(shared_ptr<Xwindow> w, int x, int y, CardInfo &m) {
    w->fillRectangle(x + 5, y + 5, 190, 170, Xwindow::Brown);
    drawATK(w, x + 10, y + 115, m.leftCorner);
    drawHP(w, x + 135, y + 115, m.rightCorner);
    ostringstream oss;
    oss << m.cost;
    drawMP(w, x + 135, y + 15, oss.str());
    w->drawString(x + 80, y + 20, m.name, Xwindow::White);
    w->drawString(x + 80, y + 40, m.type, Xwindow::Black);
    if (m.ability_cost >= 0) {
        oss.str("");
        oss << m.ability_cost;
        drawACost(w, x + 10, y + 10, oss.str());
    }
    if (m.desc != "") drawDesc(w, x, y, m.desc);
}

void GameDisplay::drawPlayer() {
    // playerBase
    w->fillRectangle(500, 20, 200, 180, Xwindow::Yellow);
    w->fillRectangle(500, 800, 200, 180, Xwindow::Yellow);
    w->fillRectangle(505, 25, 190, 170, Xwindow::Black);
    w->fillRectangle(505, 805, 190, 170, Xwindow::Black);
    // playerName
    w->drawString(580, 140, player1.name, Xwindow::Yellow);
    w->drawString(580, 850, player2.name, Xwindow::Yellow);

    ostringstream oss;
    // playerHP
    oss << player1.hp;
    drawHP(w, 510, 135, oss.str());
    oss.str("");
    oss << player2.hp;
    drawHP(w, 510, 915, oss.str());
    // playerMP
    oss.str("");
    oss << player1.mp;
    drawMP(w, 635, 140, oss.str());
    oss.str("");
    oss << player2.mp;
    drawMP(w, 635, 920, oss.str());
}

void GameDisplay::drawBoard() {
    // ritualBase
    w->fillRectangle(20, 20, 200, 180, Xwindow::Cyan);
    w->fillRectangle(20, 800, 200, 180, Xwindow::Cyan);
    w->fillRectangle(25, 25, 190, 170, Xwindow::Black);
    w->fillRectangle(25, 805, 190, 170, Xwindow::Black);
    w->drawString(90, 110, "Ritual Slot", Xwindow::Cyan);
    w->drawString(90, 890, "Ritual Slot", Xwindow::Cyan);
    // graveyardBase
    w->fillRectangle(980, 20, 200, 180, Xwindow::Magenta);
    w->fillRectangle(980, 800, 200, 180, Xwindow::Magenta);
    w->fillRectangle(985, 25, 190, 170, Xwindow::Black);
    w->fillRectangle(985, 805, 190, 170, Xwindow::Black);
    w->drawString(1040, 110, "GraveYard Slot", Xwindow::Magenta);
    w->drawString(1040, 890, "Graveyard Slot", Xwindow::Magenta);
    // minionBase
    for (int i = 0; i < 5; ++i) {
        w->fillRectangle(60 + (i * 220), 240, 200, 180, Xwindow::Orange);
        w->fillRectangle(65 + (i * 220), 245, 190, 170, Xwindow::Black);
        w->drawString(132 + (i * 220), 330, "Minion Slot", Xwindow::Orange);
    }
    for (int i = 0; i < 5; ++i) {
        w->fillRectangle(60 + (i * 220), 580, 200, 180, Xwindow::Orange);
        w->fillRectangle(65 + (i * 220), 585, 190, 170, Xwindow::Black);
        w->drawString(132 + (i * 220), 670, "Minion Slot", Xwindow::Orange);
    }
    // ritualCard
    if (ritualP1.type == "Ritual") {
        w->fillRectangle(25, 25, 190, 170, Xwindow::Brown);
        ostringstream oss;
        oss << ritualP1.cost;
        drawMP(w, 155, 35, oss.str());
        w->drawString(100, 45, ritualP1.name, Xwindow::White);
        w->drawString(100, 65, "Ritual", Xwindow::Black);
        oss.str("");
        oss << ritualP1.ability_cost;
        drawACost(w, 30, 30, oss.str());
        drawDesc(w, 20, 20, ritualP1.desc);
    }
    if (ritualP2.type == "Ritual") {
        w->fillRectangle(25, 805, 190, 170, Xwindow::Brown);
        ostringstream oss;
        oss << ritualP2.cost;
        drawMP(w, 155, 815, oss.str());
        w->drawString(100, 825, ritualP2.name, Xwindow::White);
        w->drawString(100, 845, "Ritual", Xwindow::Black);
        oss.str("");
        oss << ritualP2.ability_cost;
        drawACost(w, 30, 810, oss.str());
        drawDesc(w, 20, 800, ritualP2.desc);
    }

    // graveyardCard
    if (graveyardP1.type == "Minion") {
        drawMinion(w, 980, 20, graveyardP1);
    }
    if (graveyardP2.type == "Minion") {
        drawMinion(w, 980, 800, graveyardP2);
    }

    // minionCard
    for (int i = 0; i < minionP1.size(); ++i) {
        drawMinion(w, 60 + (i * 220), 240, minionP1[i]);
    }
    for (int i = 0; i < minionP2.size(); ++i) {
        drawMinion(w, 60 + (i * 220), 580, minionP2[i]);
    }

}

void GameDisplay::drawHand(vector<CardInfo> hand) {
    h->fillRectangle(0, 0, 1200, 240, Xwindow::Black);
    for (int i = 0; i < hand.size(); ++i) {
        if (hand[i].type == "Spell") {
            h->fillRectangle(60 + (i * 220), 20, 200, 180, Xwindow::Blue);
            h->fillRectangle(65 + (i * 220), 25, 190, 170, Xwindow::Brown);
            ostringstream oss;
            oss << hand[i].cost;
            drawMP(h, 195 + (i * 220), 35, oss.str());
            h->drawString(140 + (i * 220), 45, hand[i].name, Xwindow::White);
            h->drawString(140 + (i * 220), 65, "Spell", Xwindow::Black);
            drawDesc(h, 60 + (i * 220), 20, hand[i].desc);
        }
        else if (hand[i].type == "Ritual") {
            h->fillRectangle(60 + (i * 220), 20, 200, 180, Xwindow::Cyan);
            h->fillRectangle(65 + (i * 220), 25, 190, 170, Xwindow::Brown);
            ostringstream oss;
            oss << hand[i].cost;
            drawMP(h, 195 + (i * 220), 35, oss.str());
            h->drawString(140 + (i * 220), 45, hand[i].name, Xwindow::White);
            h->drawString(140 + (i * 220), 65, "Ritual", Xwindow::Black);
            oss.str("");
            oss << hand[i].ability_cost;
            drawACost(h, 70 + (i * 220), 30, oss.str());
            drawDesc(h, 60 + (i * 220), 20, hand[i].desc);
        }
        else if (hand[i].type == "Enchantment") {
            h->fillRectangle(60 + (i * 220), 20, 200, 180, Xwindow::Green);
            if ((hand[i].leftCorner == "") && (hand[i].rightCorner == "")) {
                h->fillRectangle(65 + (i * 220), 25, 190, 170, Xwindow::Brown);
                ostringstream oss;
                oss << hand[i].cost;
                drawMP(h, 195 + (i * 220), 35, oss.str());
                h->drawString(140 + (i * 220), 45, hand[i].name, Xwindow::White);
                h->drawString(140 + (i * 220), 65, "Enchantment", Xwindow::Black);
                drawDesc(w, 60 + (i * 220), 20, hand[i].desc);
            }
            else {
                drawMinion(h, 60 + (i * 220), 20, hand[i]);
            }
        }
        else {
            h->fillRectangle(60 + (i * 220), 20, 200, 180, Xwindow::Orange);
            drawMinion(h, 60 + (i * 220), 20, hand[i]);
        }
    }
}


