#include "game.h"
#include <memory>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    bool isTestingMode = false;
    bool isGraphicsMode = false;
    string filename1 = "default.deck"; // TODO: change this to default.deck later
    string filename2 = "default.deck"; // TODO: change this to default.deck later
    string loadfile = ""; // default empty string, means no load
    
    // args support
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-deck1") == 0) {
            filename1 = argv[i+1];
            i++;
        }
        if (strcmp(argv[i], "-deck2") == 0) {
            filename2 = argv[i+1];
            i++;
        }
        if (strcmp(argv[i], "-init") == 0) {
            loadfile = argv[i+1];
            i++;
        }
        if (strcmp(argv[i], "-testing") == 0) {
            isTestingMode = true;
        }
        if (strcmp(argv[i], "-graphics") == 0) {
            isGraphicsMode = true;
        }
    }
    
    try {
        auto game = make_unique<Game>(isTestingMode, isGraphicsMode, filename1, filename2);
        game->start(loadfile);
    } catch(string err) {
        cout << err << endl;
    }
    
}
