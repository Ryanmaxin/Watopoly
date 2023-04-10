#include "squaredisplay.h"
#include <sstream>
#include "academicbuilding.h"
using std::istringstream;

SquareDisplay::SquareDisplay(int pos, string n, SquareType st) {
    type = st;
    string name = n;
    istringstream iss {name};
    iss >> name1;
    string n2,n3;
    if (iss >> n2) {
        name2 = n2;
    }
    else {
        name2 = "";
    }
    if (iss >> n3) {
        name1 = name1+ " "+ name2;
        name2 = n3;
    }

    name1.append(7 - name1.length(), ' ');
    name2.append(7 - name2.length(), ' ');

    improvements = "";
    improvements.append(7 - improvements.length(), ' ');
    player_row = "";
    player_row.append(7 - player_row.length(), ' ');
}

ostream& SquareDisplay::printRow(ostream& out, int row, bool is_last) {
    string end = "";
    if (is_last) {
        end = "|";
    }
    switch (row)
    {
    case 0:
        out << "|-------" << end;
        break;
    case 1:
        if (type == SquareType::A) {
            out << "|" << improvements << ""<< end;
        } else {
            out << "|" << name1 << "" << end;
        }
        break;
    case 2:
        if (type == SquareType::A) {
            out << "|-------"<< end;
        } else {
            out << "|" << name2 << "" << end;
        }
        break;
    case 3:
        if (type == SquareType::A) {
            out << "|" << name1 << end;
        } else {
            out << "|" << "       " << "" << end;
        }
        break;
    case 4:
            out << "|" << player_row << ""<< end ;
        break;
    case 5:
        out << "|-------"<< end;
        break;
    }
    return out;
}

void SquareDisplay::add(char token, int i) {
    player_row[i] = token;
}
void SquareDisplay::remove(int i) {
    player_row[i] = ' ';
}

void SquareDisplay::notify(Subject *whoNotified) {
    AcademicBuilding* a = dynamic_cast<AcademicBuilding*>(whoNotified);
    if (!a) {
        #ifndef DEBUG
        cout << "Not an AcademicBuilding somehow?" << endl;
        #endif
    }
    else {
        improvements = "";
        improvements.append(7 - improvements.length(), ' ');

        int num_improvements = a->getNumberOfImprovements();
        for (int i = 0; i <num_improvements; ++i) {
            improvements[i] = 'I';
        }
    }
}
