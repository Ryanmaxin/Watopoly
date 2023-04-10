#include "controller.h"
#include "player.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int charc, char *chara[]) {
    //May need to add more if we restart game, etc
    Controller c;
    if (charc > 1) {
        string char_a = chara[1];
        if (char_a == "-testing") {
            c.setTestingMode(true);
            #ifdef DEBUG
            cout << "Testing mode enabled" << endl;
            #endif
        }
    }

    c.playMonopoly();
}
