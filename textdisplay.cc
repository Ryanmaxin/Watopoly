#include "textdisplay.h"

using namespace std;

void TextDisplay::init(Board& b) {
    for (int i = 0; i < 40; ++i) {
        Square* curr = b.getSquare(i);
        sd.push_back({curr,i});
    }
}

std::ostream &operator<<(std::ostream &out, TextDisplay &td) {
    for (int k=0;k < SIDELENGTH; ++k) {
        int offset = 1;
        if (k==9) offset = 0;
        for (int j=0; j < SQUAREHEIGHT-offset; ++j) {
            for (int i = 0; i < SIDELENGTH; ++i) {
                bool is_last_h = false;
                if (i == 9 || i == 0 && k != 0 && k != 9) is_last_h = true;
                if (k == 0) {
                    (td.sd[i+20]).printRow(out,j,is_last_h);
                }
                else if (k == 9) {
                    (td.sd[10-i]).printRow(out,j,is_last_h);
                }
                else {
                        if (k == 1 && (i != 0 && i != 9) && j == 0) {
                            (td.sd[0]).printRow(out,j,is_last_h);
                        }
                        else {
                            if (i == 0) {
                                if (k==1 && j == 0) (td.sd[20-k]).printRow(out,j,false);
                                else (td.sd[20-k]).printRow(out,j,is_last_h);
                            }
                            else if (i == 9) {
                                (td.sd[30+k]).printRow(out,j,is_last_h);
                            }
                            else {
                                    if (i == 8) cout << "       ";
                                    else cout << "        ";
                            }
                        }
                    
                }

            }
            cout << endl;
        }
    }
}
