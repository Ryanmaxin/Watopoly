#include "square.h"

#include <string>

using std::string;

Square::Square(string n): name{n} {}

string Square::getName() {
    return name;
}
