#include "square.h"
#include "enumerations.h"
#include <string>

using std::string;

Square::Square(string n, int i): name{n,i} {}

string Square::getName() { return name; }

int Square::getId() {return id;}
