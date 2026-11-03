#if !defined(_REZERWACJA_H)
#define _REZERWACJA_H
#include "Czytelnik.h"
#include "Date.h"

class Rezerwacja {
public:
    Rezerwacja(int id, int idKsiazki, int idCzytelnika, Date dataRezerwacji);
    bool sprawdzCzyPotwierdzona() const;
    static bool sprawdzCzyJestWaznaKartaBiblioteczna(Czytelnik& czytelnik);
    int getIdKsiazki() const { return idKsiazki; }
    int getIdCzytelnika() const { return idCzytelnika; }
    Date getDataRezerwacji() const { return dataRezerwacji; }
    int getId() const { return id; }

private:
    int id;
    Date dataRezerwacji;
    bool czyPotwierdzona;
    int idKsiazki;
    int idCzytelnika;
};

#endif  //_REZERWACJA_H