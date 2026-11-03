// --- KartaBiblioteczna.h ---
#if !defined(KARTABIBLIOTECZNA_H)
#define KARTABIBLIOTECZNA_H
#include "Date.h"
#include "globals.h" // Upewnij się, że jest, jeśli jest potrzebny przez jestWazna()

class KartaBiblioteczna {
private:
    int numerKarty; // Prawdopodobnie nieużywane, rozważ usunięcie
    int id;         // ID Czytelnika
    Date dataWaznosci;
    bool czyZablokowana;

public:
    // ZMIEŃ TĘ LINIĘ:
    KartaBiblioteczna() : numerKarty(0), id(0), dataWaznosci({1,1,1970}), czyZablokowana(false) {} // Ustaw false zamiast true

    // Getters and setters
    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    Date getDataWaznosci() const { return dataWaznosci; }
    void setDataWaznosci(Date date) { dataWaznosci = date; }
    bool isCzyZablokowana() const { return czyZablokowana; }
    void setCzyZablokowana(bool blocked) { czyZablokowana = blocked; }

    // Centralized validity check method
    bool jestWazna() const; // Zakładając użycie globalnej simulatedCurrentDate
    // lub bool jestWazna(const Date& dateToCheckAgainst) const;
};
#endif