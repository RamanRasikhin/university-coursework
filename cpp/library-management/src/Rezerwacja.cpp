#include "Rezerwacja.h"
#include "Czytelnik.h"


Rezerwacja::Rezerwacja(int id, int idKsiazki, int idCzytelnika, Date dataRezerwacji)
        : id(id), idKsiazki(idKsiazki), idCzytelnika(idCzytelnika),
          dataRezerwacji(dataRezerwacji), czyPotwierdzona(false) {} // Add initialization

bool Rezerwacja::sprawdzCzyPotwierdzona() const {
    return czyPotwierdzona;
}

// STATIC method - checks validity for a given reader
bool Rezerwacja::sprawdzCzyJestWaznaKartaBiblioteczna(Czytelnik& czytelnik) {
    const KartaBiblioteczna* karta = czytelnik.getKartaBiblioteczna(); // Use const getter if possible
    if (!karta) {
        return false; // No card means not valid
    }
    return karta->jestWazna(); // Use the centralized method
}