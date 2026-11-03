#include "Wypozyczenie.h"
#include "Czytelnik.h"
#include <ctime>

void Wypozyczenie::sprawdzKiedyDostepna() {
    // Implementation would check when the book will be available
}

void Wypozyczenie::przypomnijODacieZwrotu() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    Date currentDate = {ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};

    if (currentDate.year > dataZwrotu.year) {
        // Send reminder
    } else if (currentDate.year == dataZwrotu.year && currentDate.month > dataZwrotu.month) {
        // Send reminder
    } else if (currentDate.year == dataZwrotu.year && currentDate.month == dataZwrotu.month && currentDate.day >= dataZwrotu.day - 3) {
        // Send reminder 3 days before
    }
}

bool Wypozyczenie::sprawdzCzyJestWaznaKartaBiblioteczna(Czytelnik& czytelnik) {
    const KartaBiblioteczna* karta = czytelnik.getKartaBiblioteczna(); // Use const getter if possible
    if (!karta) {
        return false; // No card means not valid
    }
    return karta->jestWazna(); // Use the centralized method
}
bool Wypozyczenie::czyPrzetrzymana(const Date& currentDate) const {
    // Zwraca true, jeśli currentDate jest PÓŹNIEJ niż dataZwrotu
    return (currentDate.year > dataZwrotu.year) ||
           (currentDate.year == dataZwrotu.year && currentDate.month > dataZwrotu.month) ||
           (currentDate.year == dataZwrotu.year && currentDate.month == dataZwrotu.month && currentDate.day > dataZwrotu.day);
}