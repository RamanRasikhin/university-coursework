#include "Pracownik.h"
#include "Czytelnik.h"
#include "Ksiazka.h"
#include <vector>

void Pracownik::dodajKsiazkeDoListy(Ksiazka ksiazka) {
    listaKsiazek.push_back(ksiazka);
}

void Pracownik::usunKsiazkeDoListy(int id) {
    for (auto it = listaKsiazek.begin(); it != listaKsiazek.end(); ++it) {
        if (it->getId() == id) {
            listaKsiazek.erase(it);
            break;
        }
    }
}

void Pracownik::dodajCzytelnika(vector<Czytelnik>& czytelnicy, Czytelnik&& czytelnik) { // Use &&
    czytelnicy.push_back(std::move(czytelnik)); // Move the parameter into the vector
}

void Pracownik::usunCzytelnika(vector<Czytelnik>& czytelnicy, int id) {
    for (auto it = czytelnicy.begin(); it != czytelnicy.end(); ++it) {
        if (it->getId() == id) {
            czytelnicy.erase(it);
            break;
        }
    }
}

void Pracownik::okreslLimitKsiazek(Czytelnik& czytelnik, int limit) {
    czytelnik.setLimitKsiazek(limit);
}

void Pracownik::wyszukajKsiazke(string kryterium) {
    for (const auto& ksiazka : listaKsiazek) {
        if (ksiazka.getTytul().find(kryterium) != string::npos ||
            ksiazka.getAutor().find(kryterium) != string::npos ||
            ksiazka.getGatunek().find(kryterium) != string::npos) {
            // Display book information
        }
    }
}

void Pracownik::zalozKarteBiblioteczna(Czytelnik& czytelnik) {
    czytelnik.utworzKarteBiblioteczna();
}

void Pracownik::zablokujKarteBiblioteczna(Czytelnik& czytelnik) {
    czytelnik.getKartaBiblioteczna()->setCzyZablokowana(true);
}