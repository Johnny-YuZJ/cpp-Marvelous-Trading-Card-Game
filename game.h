#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
#include <string>
#include <istream>

class Board;
class Player;
class GameDisplay;

class Game {
private:
    bool isTestingMode;
    bool player1Setup;
    bool player2Setup;
    std::shared_ptr<Player> nonActivePlayer;
    std::shared_ptr<Player> ActivePlayer;

    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    
    std::unique_ptr<GameDisplay> display;
    
    std::shared_ptr<Board> generateBoard(bool isTestingMode);
    void generatePlayers(std::shared_ptr<Board> board);
    void generateDecks(std::string filename1, std::string filename2);
    void setupPlayerName(std::istream &input, bool console);
    void processCommand(std::string cmd, std::istream &input);
    
    void displayBoard();
    void displayHand();
    void inspect(int i);
    void printHelp();
    
public:
    Game(bool isTestingMode,
         bool isGraphicsMode,
         std::string filename1,
         std::string filename2);
    ~Game();
    
    void start(std::string loadfile); // Game loop
};
#endif
