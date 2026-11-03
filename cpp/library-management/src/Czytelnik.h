#if !defined(_CZYTELNIK_H)
#define _CZYTELNIK_H
#include "KartaBiblioteczna.h"
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr

using namespace std;
class Wypozyczenie; // Forward declaration

class Czytelnik {
public:
    Czytelnik(int id, string imie, string nazwisko, string email);

    // Explicitly default the move constructor and move assignment operator
    Czytelnik(Czytelnik&& other) noexcept = default;
    Czytelnik& operator=(Czytelnik&& other) noexcept = default;

    // Copy operations remain implicitly deleted because of unique_ptr

    // ~Czytelnik(); // Remove or default if empty after removing delete
    ~Czytelnik() = default; // Default the destructor if it became empty

    void wypozyczKsiazke(int id);
    void zarezerwujKsiazke(int id);
    void zwrocKsiazke(int id);
    void wyszukajKsiazke(int id);
    void wyszukajKsiazke(string name);
    Date getDataWaznosci() const;
    int getId() const { return id; }
    void setLimitKsiazek(int limit) { limitKsiazek = limit; }
    KartaBiblioteczna* getKartaBiblioteczna() { return kartaBiblioteczna.get(); }
    const KartaBiblioteczna* getKartaBiblioteczna() const { return kartaBiblioteczna.get(); }
    void utworzKarteBiblioteczna();
    int getLimitKsiazek() const { return limitKsiazek; }
    string getImie() const { return imie; }
    string getNazwisko() const { return nazwisko; }
    string getEmail() const { return email; }
    const vector<int>& getZarezerwowaneKsiazki() const { return zarezerwowaneKsiazki; }
    const vector<int>& getWypozyczoneKsiazki() const { return wypozyczoneKsiazki; }

private:
    int id;
    string imie;
    string nazwisko;
    string email;
    std::unique_ptr<KartaBiblioteczna> kartaBiblioteczna;
    int limitKsiazek;
    vector<int> wypozyczoneKsiazki;
    vector<int> zarezerwowaneKsiazki;
};

#endif  //_CZYTELNIK_H