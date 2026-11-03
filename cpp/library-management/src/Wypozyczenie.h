#ifndef WYPOZYCZENIE_H
#define WYPOZYCZENIE_H
#include "Date.h"

class Czytelnik;
class Wypozyczenie {
public:
    Wypozyczenie(int idKsiazki, int idCzytelnika, Date dataWypozyczenia)
            : idKsiazki(idKsiazki), idCzytelnika(idCzytelnika),
              dataWypozyczenia(dataWypozyczenia) {
        dataZwrotu = dataWypozyczenia;
        dataZwrotu.add_months(1); // Default loan duration
    }

    // NEW constructor for loading from file
    Wypozyczenie(int idKsiazki, int idCzytelnika, Date dataWypozyczenia, Date dataZwrotu)
            : idKsiazki(idKsiazki), idCzytelnika(idCzytelnika),
              dataWypozyczenia(dataWypozyczenia), dataZwrotu(dataZwrotu) {}

    // Gettery
    int getIdKsiazki() const { return idKsiazki; }
    int getIdCzytelnika() const { return idCzytelnika; }
    Date getDataZwrotu() const { return dataZwrotu; }
    Date getDataWypozyczenia() const { return dataWypozyczenia; }

    void sprawdzKiedyDostepna();
    void przypomnijODacieZwrotu();
    bool czyPrzetrzymana(const Date& currentDate) const;
    static bool sprawdzCzyJestWaznaKartaBiblioteczna(Czytelnik& czytelnik);
private:
    int idKsiazki;
    int idCzytelnika;
    Date dataWypozyczenia;
    Date dataZwrotu;


};
#endif