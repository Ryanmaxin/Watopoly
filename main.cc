#include "controller.h"
#include "player.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int charc, char *chara[]) {
    //May need to add more if we restart game, etc
    bool testing_mode = false;
    if (charc > 1) {
        string char_a = chara[1];
        if (char_a == "-testing") {
            testing_mode = true;
            #ifdef DEBUG
            cout << "Testing mode enabled" << endl;
            #endif
        }
    }

    Controller c;
    c.playMonopoly(testing_mode);
}
