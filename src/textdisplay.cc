#include "textdisplay.h"

#include <iostream>
using namespace std;

void TextDisplay::init(Board& b) {
    for (int i = 0; i < 40; ++i) {
        Square* curr = b.getSquare(i);
        string name = curr->getName();
        SquareType type;
        if (dynamic_cast<AcademicBuilding*>(curr)) {
            type = SquareType::A;
        }
        else if (dynamic_cast<Gym*>(curr)) {
            type = SquareType::G;
        }
        else if (dynamic_cast<UnownableProperty*>(curr)) {
            type = SquareType::U;
        }
        else {
            type = SquareType::R;
        }
        sd.push_back({i,name,type});
        curr->attach(&sd[i]);
    }
}

std::ostream &operator<<(std::ostream &out, TextDisplay &td) {
    for (int k=0;k < SIDELENGTH; ++k) {
        int offset = 1;
        if (k==10) offset = 0;
        for (int j=0; j < SQUAREHEIGHT-offset; ++j) {
            for (int i = 0; i < SIDELENGTH; ++i) {
                bool is_last_h = false;
                if ((i == 0) && (k != 0 && k != 10)) is_last_h = true;
                if (i == 10) is_last_h = true;
                if (k == 0) {
                    (td.sd[i+20]).printRow(out,j,is_last_h);
                }
                else if (k == 10) {
                    (td.sd[10-i]).printRow(out,j,is_last_h);
                }
                else {
                        if (k == 1 && (i != 0 && i != 10) && j == 0) {
                            (td.sd[0]).printRow(out,j,is_last_h);
                        }
                        else {
                            if (i == 0) {
                                if (k==1 && j == 0) (td.sd[20-k]).printRow(out,j,false);
                                else (td.sd[20-k]).printRow(out,j,is_last_h);
                            }
                            else if (i == 10) {
                                (td.sd[30+k]).printRow(out,j,is_last_h);
                            }
                            else {
                                    if (i == 9) out << "       ";
                                    else out << "        ";
                            }
                        }
                }

            }
            out << endl;
        }
    }
    return out;
}

void TextDisplay::notify(Subject *whoFrom) {
    Player* p = dynamic_cast<Player*>(whoFrom);
    if (!p) {
        #ifndef DEBUG
        cout << "Not a player somehow?" << endl;
        #endif
    }
    else {
        char token = p->getToken();
        int index = token_index[token];
        for (auto &square: sd) {
            square.remove(index);
        }
        int pos = p->getPosition();
        if (pos != -1) {
            sd[p->getPosition()].add(token,index);
        }
        
    }
} 

void TextDisplay::indexToken(char token,int i) {
    token_index[token] = i;
}
