#if !defined(_KSIAZKA_H)
#define _KSIAZKA_H
#include <string>
using namespace std;

class Ksiazka {
public:
    // Deklaracje metod (implementacja w .cpp)
    bool sprawdzCzyMoznaWypozyczyc() const;
    void ustawDostepnosc(bool dostepnosc);
    int getId() const;
    string getTytul() const;
    string getAutor() const;
    string getGatunek() const;
    string getOpis() const;

    // Settery inline
    void setId(int id) { this->id = id; }
    void setTytul(const string& tytul) { this->tytul = tytul; }
    void setAutor(const string& autor) { this->autor = autor; }
    void setGatunek(const string& gatunek) { this->gatunek = gatunek; }
    void setOpis(const string& opis) { this->opis = opis; }

private:
    int id;
    string tytul;
    string autor;
    string gatunek;
    bool czyMoznaWypozyczyc;
    string opis;
};

#endif