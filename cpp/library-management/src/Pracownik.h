#if !defined(_PRACOWNIK_H)
#define _PRACOWNIK_H
#include <string>
#include <vector>
#include "Czytelnik.h"
#include "Ksiazka.h"
using namespace std;

class Pracownik {
public:
    void dodajKsiazkeDoListy(Ksiazka ksiazka);
    void usunKsiazkeDoListy(int id);
    void dodajCzytelnika(vector<Czytelnik>& czytelnicy, Czytelnik&& czytelnik);
    void usunCzytelnika(vector<Czytelnik>& czytelnicy, int id);
    void okreslLimitKsiazek(Czytelnik& czytelnik, int limit);
    void wyszukajKsiazke(string kryterium);
    void zalozKarteBiblioteczna(Czytelnik& czytelnik);
    void zablokujKarteBiblioteczna(Czytelnik& czytelnik);
    vector<Ksiazka>& getListaKsiazek() { return listaKsiazek; }
    int getId() const { return id; }
    void setId(int id) { this->id = id; }
    string getImie() const { return imie; }
    void setImie(const string& imie) { this->imie = imie; }
    string getNazwisko() const { return nazwisko; }
    void setNazwisko(const string& nazwisko) { this->nazwisko = nazwisko; }
    string getEmail() const { return email; }
    void setEmail(const string& email) { this->email = email; }
private:
    int id;
    string imie;
    string nazwisko;
    string email;
    vector<Ksiazka> listaKsiazek;
};

#endif  //_PRACOWNIK_H