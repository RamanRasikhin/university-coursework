#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include "Date.h"
// Forward declarations
class Wypozyczenie;
class Rezerwacja;


extern std::vector<Wypozyczenie> wypozyczenia;
extern std::vector<Rezerwacja> rezerwacje;
extern Date simulatedCurrentDate;
#endif