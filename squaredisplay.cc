#include "squaredisplay.h"
#include <sstream>

using std::istringstream;

SquareDisplay::SquareDisplay(Square* s,int pos) {
    // if (pos == 0) type = SquareType::BR;
    // else if (pos <= 9) type = SquareType::B;
    // else if (pos == 10) type = SquareType::BL;
    // else if (pos <= 19) type = SquareType::L;
    // else if (pos == 20) type = SquareType::TL;
    // else if (pos <= 29) type = SquareType::T;
    // else if (pos == 30) type = SquareType::TR;
    // else if (pos <= 39) type = SquareType::R;
    
    underlying = s;

    if (dynamic_cast<AcademicBuilding*>(s)) {
        type = SquareType::A;
    }
    else if (dynamic_cast<Gym*>(s)) {
        type = SquareType::G;
    }
    else if (dynamic_cast<UnownableProperty*>(s)) {
        type = SquareType::U;
    }
    else if (dynamic_cast<Residence*>(s)) {
        type = SquareType::R;
    }
    


    string name = s->getName();
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

    num_improvements = 0;
    improvements = "";
    improvements.append(7 - name2.length(), ' ');
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
}
