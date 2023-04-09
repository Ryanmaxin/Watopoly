#include "controller.h"
#include "player.h"

int main(int argc, char **argv) {
    //May need to add more if we restart game, etc

    Controller c;
    if (argc == 2) {
        string str = argv[1];
        if (str == "-testing") {
            c.thetestingmode();
        }
    }
    c.playMonopoly();
}
