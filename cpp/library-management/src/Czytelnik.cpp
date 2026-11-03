#include "Czytelnik.h"
#include "KartaBiblioteczna.h"
#include "Ksiazka.h"
#include <algorithm>
#include "Wypozyczenie.h"
#include "Rezerwacja.h"
#include "FileHandler.h"
#include "globals.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Czytelnik::Czytelnik(int id, string imie, string nazwisko, string email) {
    this->id = id;
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->email = email;
    limitKsiazek = 5; // Default limit
    kartaBiblioteczna = std::make_unique<KartaBiblioteczna>(); // With this line
    if (kartaBiblioteczna) { // Good practice to check after creation/before use if needed
        kartaBiblioteczna->setId(id);
        kartaBiblioteczna->setDataWaznosci({1, 1, 2026}); // Assuming default date needed here too
    }
}
void Czytelnik::wypozyczKsiazke(int id) {
    if (wypozyczoneKsiazki.size() >= limitKsiazek) {
        throw std::runtime_error("Osiągnięto limit wypożyczonych książek");
    }

    auto it = find(wypozyczoneKsiazki.begin(), wypozyczoneKsiazki.end(), id);
    if (it != wypozyczoneKsiazki.end()) {
        throw std::runtime_error("Książka już wypożyczona");
    }

    // Tworzenie nowego wypożyczenia z aktualną datą
    Date currentDate = simulatedCurrentDate;
    wypozyczenia.emplace_back(id, this->id, currentDate);

    wypozyczoneKsiazki.push_back(id);
    FileHandler::zapiszWypozyczenia(wypozyczenia);
}

Date Czytelnik::getDataWaznosci() const { // Add const here too!
    return kartaBiblioteczna->getDataWaznosci(); // Corrected line
}

void Czytelnik::zarezerwujKsiazke(int id) {
    if (std::find(zarezerwowaneKsiazki.begin(), zarezerwowaneKsiazki.end(), id) != zarezerwowaneKsiazki.end()) {
        throw std::runtime_error("Książka już zarezerwowana");
    }
    zarezerwowaneKsiazki.push_back(id);

    static int nextId = 1;
    Rezerwacja r(nextId++, id, this->id, simulatedCurrentDate);
    rezerwacje.push_back(r);  // <--- Add this line
    FileHandler::zapiszRezerwacje(rezerwacje);
}

void Czytelnik::zwrocKsiazke(int idKsiazki) {
    // Remove from local list
    auto it_local = std::find(wypozyczoneKsiazki.begin(), wypozyczoneKsiazki.end(), idKsiazki);
    if (it_local != wypozyczoneKsiazki.end()) {
        wypozyczoneKsiazki.erase(it_local);
    } else {
        throw std::runtime_error("Ksiazka nie byla wypozyczona przez tego czytelnika");
    }

    // Remove from global list and update file
    auto it_global = std::remove_if(wypozyczenia.begin(), wypozyczenia.end(),
        [this, idKsiazki](const Wypozyczenie& w) {
            return w.getIdCzytelnika() == this->id && w.getIdKsiazki() == idKsiazki;
        });

    if (it_global != wypozyczenia.end()) {
        wypozyczenia.erase(it_global, wypozyczenia.end()); // Erase the removed elements
        FileHandler::zapiszWypozyczenia(wypozyczenia); // Save changes
    } else {
        // This case might indicate inconsistency if the book was in local list but not global
        // Or could happen if zwrocKsiazke is called multiple times for the same book.
        // Depending on desired behavior, you might log a warning or ignore.
        cerr << "Ostrzezenie: Nie znaleziono odpowiadajacego wypozyczenia w globalnej liscie dla ksiazki ID: " << idKsiazki << endl;
    }
}

void Czytelnik::wyszukajKsiazke(int id) {
    // Implementation would depend on how books are stored in the system
    // This is just a placeholder
    cout << "Wyszukiwanie książki o ID: " << id << endl;
}

void Czytelnik::wyszukajKsiazke(string name) {
    // Implementation would depend on how books are stored in the system
    // This is just a placeholder
    cout << "Wyszukiwanie książki o tytule: " << name << endl;
}
void Czytelnik::utworzKarteBiblioteczna() {
    // if (kartaBiblioteczna == nullptr) { // Check with unique_ptr
    if (!kartaBiblioteczna) {
        // kartaBiblioteczna = new KartaBiblioteczna(); // Replace this line
        kartaBiblioteczna = std::make_unique<KartaBiblioteczna>(); // With this line
        if (kartaBiblioteczna) { // Check after creation
            kartaBiblioteczna->setId(this->id);
            kartaBiblioteczna->setDataWaznosci({1, 1, 2026}); // Default date
        }
    }
}