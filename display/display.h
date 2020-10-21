#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "ascii_graphics.h"
#include "info.h"
#include <memory>
#include <vector>


class Xwindow;

class GameDisplay {
    bool graphic;
    std::shared_ptr<Xwindow> w;
    std::shared_ptr<Xwindow> h;
    std::shared_ptr<Xwindow> insM;

    PlayerInfo player1;
    PlayerInfo player2;
    std::vector<CardInfo> minionP1;
    std::vector<CardInfo> minionP2;
    CardInfo ritualP1;
    CardInfo ritualP2;
    CardInfo graveyardP1;
    CardInfo graveyardP2;


    card_template_t display_minion(CardInfo ci);
    card_template_t display_enchant(CardInfo ci);

    void boardTD();
    void handTD(std::vector<CardInfo> hand);
    void boardGD();
    void handGD(std::vector<CardInfo> hand);
    void inspectTD(std::vector<CardInfo> m);
    void inspectGD(std::vector<CardInfo> m);

    void drawBasic();
    void drawPlayer();
    void drawBoard();
    void drawHand(std::vector<CardInfo> hand);
    void drawHP(std::shared_ptr<Xwindow> w, int x, int y, std::string hp);
    void drawMP(std::shared_ptr<Xwindow> w, int x, int y, std::string mp);
    void drawATK(std::shared_ptr<Xwindow> w, int x, int y, std::string atk);
    void drawACost(std::shared_ptr<Xwindow> w, int x, int y, std::string abilityCost);
    void drawMinion(std::shared_ptr<Xwindow> w, int x, int y, CardInfo &m);
    void drawDesc(std::shared_ptr<Xwindow> w, int x, int y, std::string desc);

public:

    GameDisplay(bool graphic);
    void reset();

    void setPlayer(PlayerInfo pi, int player);
    void setMinion(std::vector<CardInfo> ci, int player);
    void setRitual(CardInfo ci, int player);
    void setGraveyard(CardInfo ci, int player);

    void boardDisplay();
    void handDisplay(std::vector<CardInfo> hand);
    void inspectMinion(std::vector<CardInfo> m);

};



#endif // !__DISPLAY_H__
