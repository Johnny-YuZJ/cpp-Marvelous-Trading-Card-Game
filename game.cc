#include "game.h"
#include "board.h"
#include "player.h"
#include "card/deck_generator.h"
#include "display/display.h"
#include "display/info.h"
#include <iostream>
#include "card/ritual/ritual.h"
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>
#include "card/card.h"

using namespace std;

Game::Game(bool isTestingMode,
           bool isGraphicsMode,
           string filename1,
           string filename2)
:isTestingMode(isTestingMode){
    
    auto board = generateBoard(isTestingMode);
    generatePlayers(board);
    generateDecks(filename1, filename2);
    player1Setup = false;
    player2Setup = false;
    display = make_unique<GameDisplay>(isGraphicsMode);
}

Game::~Game(){
    
}

shared_ptr<Board> Game::generateBoard(bool isTestingMode){
    return make_shared<Board>(isTestingMode);
}

void Game::generatePlayers(shared_ptr<Board> board) {
    p1 = make_shared<Player>(1, board);
    p2 = make_shared<Player>(2, board);
    ActivePlayer = p1;
    nonActivePlayer = p2;
}

void Game::generateDecks(string filename1, string filename2) {
    auto cardGen = make_unique<DeckGenerator>();
    
    p1->setDeck(cardGen->generate(filename1, p1, isTestingMode));
    p2->setDeck(cardGen->generate(filename2, p2, isTestingMode));
    
    p1->initHandDeck();
    p2->initHandDeck();
}

void Game::processCommand(string cmd, istream &input) {
    if (cmd == "help") {
        printHelp();
    }
    if (cmd == "quit") {
        string error = "Game end";
        throw error;
    }
    if (cmd == "end") {
        if (ActivePlayer == p1) {
            p1->endTurn();
            ActivePlayer = p2;
            nonActivePlayer = p1;
            p2->startTurn();
        } else {
            p2->endTurn();
            ActivePlayer = p1;
            nonActivePlayer = p2;
            p1->startTurn();
        }
    }
    if (cmd == "use") {
        int ally;
        int enemy;
        int target;
        string s;
        getline(input,s);
        istringstream iss(s);
        iss >> ally;
        if (iss >> enemy) {
            auto p = enemy == 1 ? p1 : p2;
            iss >> target;

            ActivePlayer->use(ally, p, target);
        }else {
            ActivePlayer->use(ally);
        }
    }
    if (cmd == "play") {
        int ally;
        int enemy;
        int target;
        string s;
        getline(input,s);
        istringstream iss(s);
        iss >> ally;
        if (iss >> enemy) {
            auto p = enemy == 1 ? p1 : p2;
            iss >> target;
            ActivePlayer->play(ally, p, target);
        }else {
            ActivePlayer->play(ally);
        }
    }
    if (cmd == "attack") {
        int ally;
        int enemy;
        string s;
        getline(input,s);
        istringstream iss(s);
        iss >> ally;
        if (iss >> enemy) {
            ActivePlayer->attack(ally, nonActivePlayer, enemy);
        }else {
            ActivePlayer->attack(ally, nonActivePlayer);
        }
    }
    if (cmd == "board") {
        displayBoard();
        //displayBoardDebug();
    }
    if (cmd == "hand") {
        displayHand();
        //displayHandDebug();
    }
    if (cmd == "inspect") {
        int i;
        input >> i;
        inspect(i);
        //inspectDebug();
    }
    if (cmd == "draw" && isTestingMode) {
        ActivePlayer->drawCard();
    }
    if (cmd == "discard" && isTestingMode) {
        int i ;
        input >> i;
        ActivePlayer->disCard(i);
    }
}

void Game::setupPlayerName(istream &input, bool console) {
    string s;
    if (!player1Setup) {
        if (console)
            cout << "What is player1's name?";
        if (input >> s) {
            p1->setName(s);
            player1Setup = true;
        } else {
            return;
        }
    }
    if (!player2Setup) {
        if (console)
            cout << "What is player2's name?";
        if (input >> s) {
            p2->setName(s);
            player2Setup = true;
            p1->startTurn();
        } else {
            return;
        }
    }
    
    
}

void Game::start(string loadfile){
    
    string cmd;
    
    if (loadfile != "") {
        ifstream file(loadfile);
        if (file.is_open()) {
            setupPlayerName(file, false);
            while(file >> cmd) {
                processCommand(cmd, file);
            }
        }
    }
    
    setupPlayerName(cin, true);
    while (cin >> cmd) {
        processCommand(cmd, cin);
    }
}

void Game::inspect(int i) {
    try {
        auto info = ActivePlayer->getBoard()->inspect(ActivePlayer->getId(), i);
        display->inspectMinion(info);
    } catch(string err) {
        cerr << err << endl;
    }
}

void Game::displayHand(){
    vector<CardInfo> handDeck = ActivePlayer->getHandDeckInfo();
    display->handDisplay(handDeck);
}

void Game::displayBoard(){
    display->reset();
    // Player 1
    PlayerInfo p1Info = p1->getPlayerInfo();
    vector<CardInfo> p1MinionSlot = p1->getBoard()->getPlayerMinionSlotInfo(1);
    
    display->setPlayer(p1Info, 1);
    display->setMinion(p1MinionSlot, 1);

    shared_ptr<Ritual> r1 = p1->getRitual();
    if(r1 != nullptr){
        CardInfo r1Info = r1->getCardInfo();
        display->setRitual(r1Info, 1);
    } else {
        display->setRitual(CardInfo{"", "", 0, 0, "", "", ""}, 1);
    }

    if (p1->hasGraveYard()) {
        CardInfo p1GraveYard = p1->getGraveYardInfo();
        display->setGraveyard(p1GraveYard, 1);
    } else {
        display->setGraveyard(CardInfo{"", "", 0, 0, "", "", ""}, 1);
    }
    
    // Player 2
    PlayerInfo p2Info = p2->getPlayerInfo();
    vector<CardInfo> p2MinionSlot = p2->getBoard()->getPlayerMinionSlotInfo(2);
    
    display->setPlayer(p2Info, 2);
    display->setMinion(p2MinionSlot, 2);

    shared_ptr<Ritual> r2 = p2->getRitual();
    if(r2 != nullptr){
        CardInfo r2Info = r2->getCardInfo();
        display->setRitual(r2Info, 2);
    } else {
        display->setRitual(CardInfo{"", "", 0, 0, "", "", ""}, 2);
    }

    if (p2->hasGraveYard()) {
        CardInfo p2GraveYard = p2->getGraveYardInfo();
        display->setGraveyard(p2GraveYard, 2);
    } else {
        display->setGraveyard(CardInfo{"", "", 0, 0, "", "", ""}, 2);
    }
    
    display->boardDisplay();
}

void Game::printHelp(){
    cout << "Commands: help -- Display this message.\n\
    end -- End the current player’s turn.\n\
    quit -- End the game.\n\
    attack minion other-minion -- Orders minion to attack other-minion.\n\
    attack minion -- Orders minion to attack the opponent.\n\
    play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n\
    use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n\
    inspect minion -- View a minion’s card and all enchantments on that minion.\n\
    hand -- Describe all cards in your hand.\n\
    board -- Describe all cards on the board." << endl;
}
