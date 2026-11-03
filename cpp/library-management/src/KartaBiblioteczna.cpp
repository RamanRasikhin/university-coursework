#include "KartaBiblioteczna.h"
#include "Date.h" // Include Date.h for getCurrentDate
#include "globals.h"

bool KartaBiblioteczna::jestWazna() const {
    if (czyZablokowana) {
        return false;
    }
    Date currentDate = simulatedCurrentDate; // Użyj globalnej symulowanej daty
    return (dataWaznosci.year > currentDate.year) ||
           (dataWaznosci.year == currentDate.year && dataWaznosci.month > currentDate.month) ||
           (dataWaznosci.year == currentDate.year && dataWaznosci.month == currentDate.month && dataWaznosci.day >= currentDate.day);
}