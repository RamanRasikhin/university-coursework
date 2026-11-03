#include "Ksiazka.h"

bool Ksiazka::sprawdzCzyMoznaWypozyczyc() const {
    return czyMoznaWypozyczyc;
}

void Ksiazka::ustawDostepnosc(bool dostepnosc) {
    czyMoznaWypozyczyc = dostepnosc;
}

int Ksiazka::getId() const {
    return id;
}

string Ksiazka::getTytul() const {
    return tytul;
}

string Ksiazka::getAutor() const {
    return autor;
}

string Ksiazka::getGatunek() const {
    return gatunek;
}

string Ksiazka::getOpis() const {
    return opis;
}