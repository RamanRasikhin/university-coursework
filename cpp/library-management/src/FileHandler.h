#if !defined(_FILEHANDLER_H)
#define _FILEHANDLER_H
#include <vector>
#include <string>
#include "Czytelnik.h"
#include "Pracownik.h"
#include "Ksiazka.h"
#include "Rezerwacja.h"
#include "Wypozyczenie.h"

using namespace std;

class FileHandler {
public:
    static vector<Czytelnik> wczytajCzytelnikow();
    static vector<Pracownik> wczytajPracownikow();
    static vector<Ksiazka> wczytajKsiazki();
    static vector<vector<string>> wczytajKonta();
    static void zapiszCzytelnikow(const vector<Czytelnik>& czytelnicy);
    static void zapiszKsiazki(const vector<Ksiazka>& ksiazki);
    static void zapiszKonto(const string& login, const string& haslo, const string& typ, int id);
    static void zapiszPracownikow(const vector<Pracownik> &pracownicy);
    static vector<Rezerwacja> wczytajRezerwacje();
    static vector<Wypozyczenie> wczytajWypozyczenia();
    static void zapiszRezerwacje(const vector<Rezerwacja>& rezerwacje);
    static void zapiszWypozyczenia(const vector<Wypozyczenie>& wypozyczenia);
    static string getPath(const std::string& filename);

    static string base_path;
};

#endif