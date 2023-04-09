#include "controller.h"
#include "player.h"

int main(int charc, char *chara[]) {
    //May need to add more if we restart game, etc

    Controller c;
    c.playMonopoly();

    if (charc > 1) {
        string char_a = chara[1];
        if (char_a == "-testing") {
            c->testingmode();
        }
    }

}