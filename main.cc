#include "controller.h"
#include "player.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    //May need to add more if we restart game, etc
    Controller c;
    if (argc > 1) {
        string str = argv[1];
        if (str == "-testing") {
            c.setTestingMode(true);
            #ifdef DEBUG
            cout << "Testing mode enabled" << endl;
            #endif
        }
        // using if to indicate possibility of the merge of two test and load commands together
        if (str == "-load") {
            // file is the third argument
            c.setIsLoaded(true);
            string file = argv[2];
            c.setLoadedFile(file);
        }
    }
    c.playMonopoly();
}
