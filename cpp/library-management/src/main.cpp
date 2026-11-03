#include "Czytelnik.h"
#include "Pracownik.h"
#include "Ksiazka.h"
#include "FileHandler.h"
#include "Rezerwacja.h"
#include "Date.h"
#include "Wypozyczenie.h"
#include "globals.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<Czytelnik> czytelnicy;
vector<Pracownik> pracownicy;
vector<Ksiazka> ksiazki;
vector<vector<string>> konta;
int calculate_new_id(const std::vector<Czytelnik>& czytelnicy) {
    if (czytelnicy.empty()) {
        return 1;
    }
    auto max_it = std::max_element(czytelnicy.begin(), czytelnicy.end(),
                                   [](const Czytelnik& a, const Czytelnik& b) {
                                       return a.getId() < b.getId();
                                   });
    return max_it->getId() + 1;
}
void symulujCzas() {
    int wybor;
    do {
        cout << "\n--- SYMULACJA CZASU ---";
        cout << "\nAktualna symulowana data: " << simulatedCurrentDate.to_string() << endl;
        cout << "Rzeczywista data systemowa: " << Date::getCurrentDate().to_string() << endl; // Dla porównania
        cout << "-------------------------\n";
        cout << "1. Dodaj miesiace\n";
        cout << "2. Odejmij miesiace\n";
        cout << "3. Resetuj do daty rzeczywistej\n";
        cout << "4. Powrot do menu glownego\n";
        cout << "Wybor: ";

        while (!(cin >> wybor)) {
             cout << "Nieprawidlowy wybor. Podaj numer: ";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj newline

        switch (wybor) {
            case 1: {
                int miesiace;
                cout << "Podaj liczbe miesiecy do dodania: ";
                while (!(cin >> miesiace) || miesiace <= 0) {
                     cout << "Podaj dodatnia liczbe calkowita: ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                simulatedCurrentDate.add_months(miesiace);
                cout << "Dodano " << miesiace << " miesiecy. Nowa symulowana data: " << simulatedCurrentDate.to_string() << endl;
                break;
            }
            case 2: {
                 int miesiace;
                cout << "Podaj liczbe miesiecy do odjecia: ";
                 while (!(cin >> miesiace) || miesiace <= 0) {
                     cout << "Podaj dodatnia liczbe calkowita: ";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                simulatedCurrentDate.add_months(-miesiace); // Odejmujemy przekazując ujemną wartość
                cout << "Odjeto " << miesiace << " miesiecy. Nowa symulowana data: " << simulatedCurrentDate.to_string() << endl;
                break;
            }
            case 3: {
                simulatedCurrentDate = Date::getCurrentDate();
                cout << "Symulowana data zresetowana do daty rzeczywistej: " << simulatedCurrentDate.to_string() << endl;
                break;
            }
            case 4: {
                cout << "Powrot do menu glownego...\n";
                break;
            }
            default:
                cout << "Nieznana opcja.\n";
                break;
        }

    } while (wybor != 4);
}
void zaladujDane() {
    czytelnicy = FileHandler::wczytajCzytelnikow();
    pracownicy = FileHandler::wczytajPracownikow();
    ksiazki = FileHandler::wczytajKsiazki();
    konta = FileHandler::wczytajKonta();
    rezerwacje = FileHandler::wczytajRezerwacje();  // Dodane
    wypozyczenia = FileHandler::wczytajWypozyczenia(); // Dodane
}

// DODANE: Funkcja pomocnicza do wyszukiwania książek
void wyszukajKsiazke() {
    int wybor;
    cout << "Szukaj po:\n1. ID\n2. Tytule\n3. Autorze\n4. Gatunku\nWybor: ";
    cin >> wybor;
    cin.ignore();

    string kryterium;
    cout << "Podaj szukana fraze: ";
    getline(cin, kryterium);

    for (const auto& k : ksiazki) {
        bool match = false;
        switch(wybor) {
            case 1:
                if (to_string(k.getId()) == kryterium) match = true;
                break;
            case 2:
                if (k.getTytul().find(kryterium) != string::npos) match = true;
                break;
            case 3:
                if (k.getAutor().find(kryterium) != string::npos) match = true;
                break;
            case 4:
                if (k.getGatunek().find(kryterium) != string::npos) match = true;
                break;
        }
        if (match) {
            cout << k.getId() << " | " << k.getTytul()
                 << " | " << k.getAutor() << " | "
                 << (k.sprawdzCzyMoznaWypozyczyc() ? "Dostepna" : "Niedostepna") << endl;
        }
    }
}

void menuCzytelnika(Czytelnik& czytelnik) {
    int wybor;
    do {
        cout << "\n--- MENU CZYTELNIKA ---\n";
        cout << "1. Wypozycz ksiazke\n";
        cout << "2. Zwroc ksiazke\n";
        cout << "3. Zarezerwuj ksiazke\n";
        cout << "4. Moje rezerwacje\n";
        cout << "5. Moje wypozyczenia\n";
        cout << "6. Wyszukaj ksiazke\n";
        cout << "7. Wyswietl moje dane\n";
        cout << "8. Wyjdz\n";
        cout << "Wybor: ";
        cin >> wybor;

        try {
            switch(wybor) {
                case 1: {
                    int id;
                    cout << "Podaj ID ksiazki: ";
                    cin >> id;
                    czytelnik.wypozyczKsiazke(id);
                    // Aktualizacja statusu książki
                    for (auto& k : ksiazki) {
                        if (k.getId() == id) k.ustawDostepnosc(false);
                    }
                    FileHandler::zapiszKsiazki(ksiazki);
                    cout << "Wypozyczono ksiazke!\n";
                    break;
                }
                case 2: {
                    int id;
                    cout << "Podaj ID ksiazki: ";
                    cin >> id;
                    czytelnik.zwrocKsiazke(id);
                    for (auto& k : ksiazki) {
                        if (k.getId() == id) k.ustawDostepnosc(true);
                    }

                    // Check reservations for this book
                    auto it = find_if(rezerwacje.begin(), rezerwacje.end(), [id](const Rezerwacja& r) {
                        return r.getIdKsiazki() == id;
                    });

                    if (it != rezerwacje.end()) {
                        // Loan to the first reserving user
                        Czytelnik& reservingUser = *find_if(czytelnicy.begin(), czytelnicy.end(),
                                                            [&](const Czytelnik& c) { return c.getId() == it->getIdCzytelnika(); });

                        try {
                            reservingUser.wypozyczKsiazke(id);
                            // Update book availability again
                            for (auto& k : ksiazki) {
                                if (k.getId() == id) k.ustawDostepnosc(false);
                            }
                            // Remove the reservation
                            rezerwacje.erase(it);
                            FileHandler::zapiszRezerwacje(rezerwacje);
                        } catch (const exception& e) {
                            cerr << "Blad przy automatycznym wypozyczeniu: " << e.what() << endl;
                        }
                    }

                    FileHandler::zapiszKsiazki(ksiazki);
                    cout << "Zwrocono ksiazke!\n";
                    break;
                }
                case 3: {
                    int id;
                    cout << "Podaj ID ksiazki: ";
                    cin >> id;
                    czytelnik.zarezerwujKsiazke(id);
                    cout << "Zarezerwowano ksiazke!\n";
                    break;
                }
                case 4: {
                    cout << "\nMOJE REZERWACJE:\n";
                    for (int id : czytelnik.getZarezerwowaneKsiazki()) {
                        for (auto& k : ksiazki) {
                            if (k.getId() == id) {
                                cout << k.getTytul() << " (ID: " << id << ")\n";
                            }
                        }
                    }
                    break;
                }
                case 5: {
                    cout << "\nMOJE WYPOZYCZENIA:\n";
                    for (int id : czytelnik.getWypozyczoneKsiazki()) {
                        for (auto& k : ksiazki) {
                            if (k.getId() == id) {
                                cout << k.getTytul() << " (ID: " << id << ")\n";
                            }
                        }
                    }
                    break;
                }
                case 6:
                    wyszukajKsiazke();
                    break;
                case 7: {
                    cout << "\nDANE CZYTELNIKA:\n";
                    cout << "ID: " << czytelnik.getId() << "\n";
                    cout << "Imie: " << czytelnik.getImie() << "\n";
                    cout << "Nazwisko: " << czytelnik.getNazwisko() << "\n";
                    cout << "Limit ksiazek: " << czytelnik.getLimitKsiazek() << "\n";
                    break;
                }
            }
        } catch (const exception& e) {
            cerr << "Blad: " << e.what() << endl;
        }
    } while (wybor != 8);
}


void menuPracownika(Pracownik& pracownik) {
    int wybor;
    do {
        cout << "\n--- MENU PRACOWNIKA ---\n";
        cout << "1. Dodaj ksiazke\n";
        cout << "2. Usun ksiazke\n";
        cout << "3. Przegladaj wszystkie ksiazki\n";
        cout << "4. Zarzadzaj czytelnikami\n";
        cout << "5. Wyszukaj ksiazke\n";
        cout << "6. Przedluz waznosc karty\n";
        cout << "7. Zablokuj/Odblokuj karte\n"; // Zmieniono opis
        cout << "8. Przegladaj rezerwacje\n";
        cout << "9. Przegladaj wypozyczenia\n";
        cout << "10. Sprawdz waznosc karty czytelnika\n"; // NEW OPTION
        cout << "11. Wyjdz\n";
        cout << "Wybor: ";

        // --- Lepsza obsługa błędów wejścia ---
        while (!(cin >> wybor)) {
             cout << "Nieprawidlowy wybor. Podaj numer: ";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // --- Koniec obsługi błędów ---

        try {
            switch(wybor) {
                // --- (case 1, 2, 3 - bez zmian) ---
                 case 1: {
                    Ksiazka k;
                    string tytul, autor, gatunek, opis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki z poprzedniego cin
                    cout << "Tytul: "; getline(cin, tytul);
                    cout << "Autor: "; getline(cin, autor);
                    cout << "Gatunek: "; getline(cin, gatunek);
                    cout << "Opis: "; getline(cin, opis);

                    // Lepsze generowanie ID dla książki
                    int new_book_id = 1;
                    if (!ksiazki.empty()) {
                       auto max_it = std::max_element(ksiazki.begin(), ksiazki.end(),
                                                       [](const Ksiazka& a, const Ksiazka& b) {
                                                           return a.getId() < b.getId();
                                                       });
                       if (max_it != ksiazki.end()) {
                            new_book_id = max_it->getId() + 1;
                       }
                    }

                    k.setId(new_book_id);
                    k.setTytul(tytul);
                    k.setAutor(autor);
                    k.setGatunek(gatunek);
                    k.setOpis(opis);
                    k.ustawDostepnosc(true);

                    ksiazki.push_back(k); // push_back jest ok dla Ksiazka (nie ma unique_ptr)
                    FileHandler::zapiszKsiazki(ksiazki);
                    cout << "Ksiazka dodana! ID: " << k.getId() << endl;
                    break;
                }

                case 2: {
                    int id;
                    cout << "Podaj ID ksiazki do usuniecia: ";
                     while (!(cin >> id)) { // Obsługa błędu wejścia
                        cout << "Nieprawidlowe ID. Podaj numer: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     }

                    // Sprawdzenie czy książka nie jest wypożyczona lub zarezerwowana
                     bool can_delete = true;
                     for(const auto& w : wypozyczenia) {
                         if (w.getIdKsiazki() == id) {
                             cout << "Blad: Nie mozna usunac ksiazki, poniewaz jest aktualnie wypozyczona przez czytelnika ID: " << w.getIdCzytelnika() << endl;
                             can_delete = false;
                             break;
                         }
                     }
                     if (can_delete) {
                         for(const auto& r : rezerwacje) {
                             if (r.getIdKsiazki() == id) {
                                 cout << "Blad: Nie mozna usunac ksiazki, poniewaz jest aktualnie zarezerwowana przez czytelnika ID: " << r.getIdCzytelnika() << endl;
                                 can_delete = false;
                                 break;
                             }
                         }
                     }


                    if (can_delete) {
                        auto it = remove_if(ksiazki.begin(), ksiazki.end(),
                                            [id](const Ksiazka& k) { return k.getId() == id; });

                        if(it != ksiazki.end()) {
                            ksiazki.erase(it, ksiazki.end());
                            FileHandler::zapiszKsiazki(ksiazki);
                            cout << "Ksiazka usunieta!\n";
                        } else {
                            cout << "Nie znaleziono ksiazki o podanym ID!\n";
                        }
                    }
                    break;
                }

                case 3: {
                    cout << "\n--- WSZYSTKIE KSIAZKI ---\n";
                    if (ksiazki.empty()) {
                        cout << "Brak ksiazek w systemie.\n";
                    } else {
                        for(const auto& k : ksiazki) {
                            cout << "ID: " << k.getId()
                                 << " | Tytul: " << k.getTytul()
                                 << " | Autor: " << k.getAutor()
                                 << " | Status: " << (k.sprawdzCzyMoznaWypozyczyc() ? "Dostepna" : "Wypozyczona/Zarezerwowana") // Zmieniono opis statusu
                                 << endl;
                        }
                    }
                    break;
                }

                case 4: { // Zarządzaj czytelnikami - Zmodyfikowany case
                    int opcja_czytelnik;
                    do {
                        cout << "\n--- ZARZADZANIE CZYTELNIKAMI ---\n";
                        cout << "1. Dodaj czytelnika\n";
                        cout << "2. Usun czytelnika\n";
                        cout << "3. Zmien limit ksiazek\n";
                        cout << "4. Wyswietl wszystkich czytelnikow\n"; // NOWA OPCJA
                        cout << "5. Powrot do menu pracownika\n";       // NOWA OPCJA (Wyjście)
                        cout << "Wybor: ";

                        while (!(cin >> opcja_czytelnik)) {
                             cout << "Nieprawidlowy wybor. Podaj numer: ";
                             cin.clear();
                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Zawsze ignoruj resztki po wczytaniu numeru opcji

                        if(opcja_czytelnik == 1) {
                            string imie, nazwisko, email, login, haslo;
                            // cin.ignore(); // Już jest wyżej
                            cout << "Imie: "; getline(cin, imie);
                            cout << "Nazwisko: "; getline(cin, nazwisko);
                            cout << "Email: "; getline(cin, email);
                            cout << "Login: "; getline(cin, login); // Pobierz login dla nowego konta
                            cout << "Haslo: "; getline(cin, haslo); // Pobierz hasło dla nowego konta

                            // Sprawdzenie czy login już istnieje
                            bool loginExists = false;
                            for(const auto& acc : konta) {
                                if (acc.size() > 0 && acc[0] == login) {
                                    loginExists = true;
                                    break;
                                }
                            }

                            if (loginExists) {
                                cout << "Blad: Login '" << login << "' juz istnieje. Wybierz inny.\n";
                            } else {
                                int new_id = calculate_new_id(czytelnicy); // Użyj funkcji pomocniczej
                                Czytelnik c(new_id, imie, nazwisko, email);
                                czytelnicy.push_back(std::move(c)); // Użyj move
                                FileHandler::zapiszCzytelnikow(czytelnicy);
                                FileHandler::zapiszKonto(login, haslo, "czytelnik", new_id); // Zapisz nowe konto
                                konta = FileHandler::wczytajKonta(); // Odśwież listę kont w pamięci
                                cout << "Czytelnik dodany! ID: " << new_id << ", Login: " << login << endl;
                            }
                        }
                        else if(opcja_czytelnik == 2) {
                            int id;
                            cout << "Podaj ID czytelnika do usuniecia: ";
                            while (!(cin >> id)) {
                                cout << "Nieprawidlowe ID. Podaj numer: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                            // Sprawdzenie czy czytelnik ma wypożyczone książki
                            bool hasLoans = false;
                            for (const auto& w : wypozyczenia) {
                                if (w.getIdCzytelnika() == id) {
                                    hasLoans = true;
                                    break;
                                }
                            }
                             // Sprawdzenie czy czytelnik ma rezerwacje
                             bool hasReservations = false;
                             for (const auto& r : rezerwacje) {
                                 if (r.getIdCzytelnika() == id) {
                                     hasReservations = true;
                                     break;
                                 }
                             }


                            if (hasLoans) {
                                cout << "Blad: Nie mozna usunac czytelnika, poniewaz ma aktywne wypozyczenia.\n";
                            } else if (hasReservations) {
                                cout << "Blad: Nie mozna usunac czytelnika, poniewaz ma aktywne rezerwacje.\n";
                            }
                             else {
                                // Usuwanie czytelnika z wektora czytelnikow
                                auto it_czytelnik = std::remove_if(czytelnicy.begin(), czytelnicy.end(),
                                                                   [id](const Czytelnik& c) { return c.getId() == id; });
                                bool removed = false;
                                if (it_czytelnik != czytelnicy.end()) {
                                    czytelnicy.erase(it_czytelnik, czytelnicy.end());
                                    FileHandler::zapiszCzytelnikow(czytelnicy);
                                    removed = true;
                                }

                                if (removed) {
                                    // Usuwanie konta powiązanego z czytelnikiem
                                    auto it_konto = std::remove_if(konta.begin(), konta.end(),
                                                                  [id](const vector<string>& k) {
                                                                      // Sprawdź rozmiar i typ przed konwersją ID
                                                                      return k.size() == 4 && k[2] == "czytelnik" && stoi(k[3]) == id;
                                                                  });
                                    if (it_konto != konta.end()) {
                                        konta.erase(it_konto, konta.end());
                                        // Zapisz zaktualizowaną listę kont (potrzebna funkcja zapisująca wszystkie konta)
                                        // FileHandler::zapiszWszystkieKonta(konta); // POTRZEBNA NOWA FUNKCJA w FileHandler
                                        // Tymczasowe obejście: nadpisz plik konta.csv ręcznie lub zaimplementuj funkcję
                                        ofstream konto_file("konta.csv"); // Nadpisuje plik
                                        for(const auto& k : konta) {
                                            if (k.size() == 4) { // Zapisuj tylko poprawne wpisy
                                                konto_file << k[0] << ";" << k[1] << ";" << k[2] << ";" << k[3] << "\n";
                                            }
                                        }
                                        cout << "Czytelnik i powiazane konto usuniete!\n";
                                    } else {
                                        cout << "Czytelnik usuniety, ale nie znaleziono powiazanego konta (lub blad w danych konta).\n";
                                    }
                                } else {
                                    cout << "Nie znaleziono czytelnika o podanym ID!\n";
                                }
                            }
                        }
                        else if(opcja_czytelnik == 3) {
                            int id, limit;
                            cout << "Podaj ID czytelnika: ";
                            while (!(cin >> id)) {
                                cout << "Nieprawidlowe ID. Podaj numer: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cout << "Nowy limit (liczba > 0): ";
                             while (!(cin >> limit) || limit <= 0) {
                                cout << "Nieprawidlowy limit. Podaj liczbe dodatnia: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                            bool found = false;
                            for(auto& c : czytelnicy) {
                                if(c.getId() == id) {
                                    pracownik.okreslLimitKsiazek(c, limit); // Ta metoda jest w Pracownik.cpp
                                    FileHandler::zapiszCzytelnikow(czytelnicy);
                                    cout << "Limit ksiazek dla czytelnika ID " << id << " zmieniony na " << limit << "!\n";
                                    found = true; // Ustaw flagę, że znaleziono
                                    break; // Wyjdź z pętli po znalezieniu
                                }
                            }
                            if (!found) { // Sprawdź flagę po pętli
                                cout << "Czytelnik o ID " << id << " nie znaleziony!\n";
                            }
                        }
                        else if(opcja_czytelnik == 4) { // NOWA OPCJA - Wyświetl wszystkich
                            cout << "\n--- WSZYSCY CZYTELNICY ---\n";
                            if (czytelnicy.empty()) {
                                cout << "Brak zarejestrowanych czytelnikow.\n";
                            } else {
                                for(const auto& c : czytelnicy) {
                                    cout << "ID: " << c.getId()
                                         << " | Imie: " << c.getImie()
                                         << " | Nazwisko: " << c.getNazwisko()
                                         << " | Email: " << c.getEmail()
                                         << " | Limit: " << c.getLimitKsiazek();
                                    // Dodatkowo pokaż status karty
                                    if (c.getKartaBiblioteczna()) {
                                        cout << " | Karta wazna do: " << c.getDataWaznosci().to_string()
                                             << " | Karta zablokowana: " << (c.getKartaBiblioteczna()->isCzyZablokowana() ? "Tak" : "Nie");
                                    } else {
                                        cout << " | Karta: Brak";
                                    }
                                    cout << endl;
                                }
                            }
                             cout << "\nNacisnij Enter, aby kontynuowac...";
                             // cin.ignore(); // Już było wyżej
                             cin.get(); // Czeka na Enter
                        }
                        else if (opcja_czytelnik == 5) {
                            cout << "Powrot do menu glownego pracownika...\n";
                        }
                        else {
                            cout << "Nieznana opcja.\n";
                        }

                    } while (opcja_czytelnik != 5); // Pętla działa dopóki nie wybierze się 5
                    break; // Wyjście z case 4 po zakończeniu pętli podmenu
                } // Koniec case 4

                // --- (case 5 - bez zmian) ---
                 case 5: {
                    wyszukajKsiazke(); // Użyj istniejącej funkcji
                    break;
                }


                case 6: { // Przedłuż ważność karty
                    int id;
                    cout << "Podaj ID czytelnika, ktoremu chcesz przedluzyc karte: ";
                     while (!(cin >> id)) {
                        cout << "Nieprawidlowe ID. Podaj numer: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                    bool found = false;
                    for(auto& c : czytelnicy) {
                        if(c.getId() == id) {
                             if(c.getKartaBiblioteczna()) { // Sprawdź czy karta istnieje
                                Date nowaData = c.getDataWaznosci();
                                int miesiace;
                                cout << "O ile miesiecy przedluzyc waznosc karty? ";
                                while (!(cin >> miesiace) || miesiace <= 0) {
                                     cout << "Podaj dodatnia liczbe miesiecy: ";
                                     cin.clear();
                                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                                nowaData.add_months(miesiace); // Użyj metody z Date.cpp
                                c.getKartaBiblioteczna()->setDataWaznosci(nowaData); // Użyj settera
                                FileHandler::zapiszCzytelnikow(czytelnicy);
                                cout << "Waznosc karty przedluzona. Nowa data waznosci: " << nowaData.to_string() << endl;
                             } else {
                                 cout << "Blad: Ten czytelnik nie posiada karty bibliotecznej.\n";
                             }
                            found = true;
                            break;
                        }
                    }
                     if (!found) {
                         cout << "Nie znaleziono czytelnika o podanym ID!\n";
                     }
                    break;
                }

                case 7: { // Zablokuj/Odblokuj kartę
                    int id;
                    cout << "Podaj ID czytelnika, ktorego karte chcesz zablokowac/odblokowac: ";
                    while (!(cin >> id)) {
                        cout << "Nieprawidlowe ID. Podaj numer: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                    bool found = false;
                    for(auto& c : czytelnicy) {
                        if(c.getId() == id) {
                             if (c.getKartaBiblioteczna()) {
                                 bool jestZablokowana = c.getKartaBiblioteczna()->isCzyZablokowana();
                                 cout << "Karta jest aktualnie " << (jestZablokowana ? "ZABLOKOWANA" : "AKTYWNA") << ".\n";
                                 cout << "Czy chcesz zmienic status? (t/n): ";
                                 char decyzja;
                                 cin >> decyzja;
                                  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj resztki

                                 if (decyzja == 't' || decyzja == 'T') {
                                     c.getKartaBiblioteczna()->setCzyZablokowana(!jestZablokowana); // Odwróć status
                                     FileHandler::zapiszCzytelnikow(czytelnicy);
                                     cout << "Status karty zostal zmieniony na: " << (!jestZablokowana ? "ZABLOKOWANA" : "AKTYWNA") << "!\n";
                                 } else {
                                     cout << "Status karty pozostal bez zmian.\n";
                                 }
                             } else {
                                 cout << "Blad: Ten czytelnik nie posiada karty bibliotecznej.\n";
                             }
                            found = true;
                            break; // Exit the loop after finding and processing
                        }
                    }
                    if (!found) { // Print message only if loop finished without finding
                        cout << "Nie znaleziono czytelnika!\n";
                    }
                    break; // Break for the switch statement
                }


                case 8: { // Przeglądaj rezerwacje
                    // rezerwacje = FileHandler::wczytajRezerwacje(); // Niepotrzebne ponowne wczytywanie, jeśli dane są globalne i aktualne
                    cout << "\n--- WSZYSTKIE REZERWACJE ---\n";
                     if (rezerwacje.empty()) {
                         cout << "Brak aktywnych rezerwacji.\n";
                     } else {
                        for (const auto& r : rezerwacje) {
                            // Wyszukaj tytuł książki i dane czytelnika dla lepszego wyświetlania
                            string tytulKsiazki = "Nieznany (ID: " + to_string(r.getIdKsiazki()) + ")";
                            string daneCzytelnika = "Nieznany (ID: " + to_string(r.getIdCzytelnika()) + ")";

                            for(const auto& k : ksiazki) { if (k.getId() == r.getIdKsiazki()) { tytulKsiazki = k.getTytul(); break; } }
                            for(const auto& c : czytelnicy) { if (c.getId() == r.getIdCzytelnika()) { daneCzytelnika = c.getImie() + " " + c.getNazwisko(); break; } }

                            cout << "ID Rezerwacji: " << r.getId() // Dodano ID rezerwacji
                                 << " | Ksiazka: " << tytulKsiazki
                                 << " | Czytelnik: " << daneCzytelnika
                                 << " | Data: " << r.getDataRezerwacji().to_string() << endl;
                        }
                     }
                     cout << "\nNacisnij Enter, aby kontynuowac...";
                     // cin.ignore(); // Może być potrzebne w zależności od poprzednich operacji
                     cin.get(); // Czeka na Enter
                    break;
                }

                case 9: { // Przeglądaj wypożyczenia
                    // wypozyczenia = FileHandler::wczytajWypozyczenia(); // Niepotrzebne ponowne wczytywanie
                     Date currentDate = simulatedCurrentDate;

                    cout << "\n--- AKTYWNE WYPOZYCZENIA ---\n";
                     if (wypozyczenia.empty()) {
                         cout << "Brak aktywnych wypozyczen.\n";
                     } else {
                        for (const auto& w : wypozyczenia) {
                             // Wyszukaj tytuł książki i dane czytelnika
                            string tytulKsiazki = "Nieznany (ID: " + to_string(w.getIdKsiazki()) + ")";
                            string daneCzytelnika = "Nieznany (ID: " + to_string(w.getIdCzytelnika()) + ")";

                            for(const auto& k : ksiazki) { if (k.getId() == w.getIdKsiazki()) { tytulKsiazki = k.getTytul(); break; } }
                            for(const auto& c : czytelnicy) { if (c.getId() == w.getIdCzytelnika()) { daneCzytelnika = c.getImie() + " " + c.getNazwisko(); break; } }

                            cout << "Ksiazka: " << tytulKsiazki
                                 << " | Czytelnik: " << daneCzytelnika
                                 << " | Wypozyczono: " << w.getDataWypozyczenia().to_string()
                                 << " | Zwrot do: " << w.getDataZwrotu().to_string()
                                 << " | Status: " << (w.czyPrzetrzymana(currentDate) ? "PO TERMINIE" : "W TERMINIE")
                                 << endl;
                        }
                     }
                      cout << "\nNacisnij Enter, aby kontynuowac...";
                     // cin.ignore();
                     cin.get(); // Czeka na Enter
                    break;
                }

                case 10: { // NEW CASE: Check Card Validity
                    int idCzytelnika;
                    cout << "Podaj ID czytelnika do sprawdzenia karty: ";
                    while (!(cin >> idCzytelnika)) {
                        cout << "Nieprawidlowe ID. Podaj numer: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline

                    auto it = find_if(czytelnicy.begin(), czytelnicy.end(),
                                      [idCzytelnika](const Czytelnik& c){ return c.getId() == idCzytelnika; });

                    if (it != czytelnicy.end()) {
                        const Czytelnik& czytelnik = *it;
                        const KartaBiblioteczna* karta = czytelnik.getKartaBiblioteczna();

                        if (karta) {
                            cout << "Karta czytelnika: " << czytelnik.getImie() << " " << czytelnik.getNazwisko() << " (ID: " << czytelnik.getId() << ")\n";
                            cout << "Data waznosci: " << karta->getDataWaznosci().to_string() << "\n";
                            cout << "Czy zablokowana: " << (karta->isCzyZablokowana() ? "Tak" : "Nie") << "\n";
                            cout << "Status wg symulowanej daty (" << simulatedCurrentDate.to_string() << "): ";
                            if (karta->jestWazna()) {
                                cout << "WAZNA\n";
                            } else {
                                cout << "NIEWAZNA (lub zablokowana)\n";
                            }
                        } else {
                            cout << "Czytelnik o ID " << idCzytelnika << " nie posiada karty bibliotecznej.\n";
                        }
                    } else {
                        cout << "Nie znaleziono czytelnika o ID " << idCzytelnika << ".\n";
                    }
                     cout << "\nNacisnij Enter, aby kontynuowac...";
                     cin.get(); // Czeka na Enter
                    break;
                }

                case 11: // Adjusted exit case number
                     cout << "Wylogowywanie...\n";
                     break;

                 default:
                     cout << "Nieprawidlowy wybor.\n";
                     break;

            } // Koniec switch
        } catch(const exception& e) {
            cerr << "Blad: " << e.what() << endl;
            // Lepsze czyszczenie strumienia po błędzie
            cin.clear(); // Wyczyść flagi błędów cin
            // Ignoruj wszystko w buforze aż do nowej linii
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch(...) { // Złap wszystkie inne wyjątki
             cerr << "Wystapil nieznany blad!" << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while(wybor != 11); // Pętla menu pracownika
}

void rejestracja() {
    string login, haslo, typ, imie, nazwisko, email;
    cout << "Podaj login: ";
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Typ czytelnik/pracownik(cz/pr): ";
    cin >> typ;
    cin.ignore();

    if (typ == "cz") {
        cout << "Podaj imie: ";
        getline(cin, imie);
        cout << "Podaj nazwisko: ";
        getline(cin, nazwisko);
        cout << "Podaj email: ";
        getline(cin, email);
        auto max_id = max_element(czytelnicy.begin(), czytelnicy.end(),
                                  [](const Czytelnik& a, const Czytelnik& b) { return a.getId() < b.getId(); });

        int new_id = (max_id != czytelnicy.end()) ? max_id->getId() + 1 : 1;
        Czytelnik c(new_id, imie, nazwisko, email);
        czytelnicy.push_back(std::move(c));
        FileHandler::zapiszKonto(login, haslo, typ, c.getId());
        FileHandler::zapiszCzytelnikow(czytelnicy);
        cout << "Zarejestrowano czytelnika!\n";
    }
    else if (typ == "pr") {
        cout << "Podaj imie: ";
        getline(cin, imie);
        cout << "Podaj nazwisko: ";
        getline(cin, nazwisko);
        cout << "Podaj email: ";
        getline(cin, email);

        Pracownik p;
        auto max_pracownik = max_element(pracownicy.begin(), pracownicy.end(),
                                                     [](const Pracownik& a, const Pracownik& b) { return a.getId() < b.getId(); });
        int new_id = (max_pracownik != pracownicy.end()) ? max_pracownik->getId() + 1 : 1;
        p.setId(new_id);
        p.setImie(imie);
        p.setNazwisko(nazwisko);
        p.setEmail(email);
        pracownicy.push_back(p);
        FileHandler::zapiszKonto(login, haslo, typ, p.getId());
        FileHandler::zapiszPracownikow(pracownicy);
        cout << "Zarejestrowano pracownika!\n";
    }

    // Odśwież dane po rejestracji
    konta = FileHandler::wczytajKonta();
}

void logowanie() {
    string login, haslo;
    cout << "Login: ";
    cin >> login;
    cout << "Haslo: ";
    cin >> haslo;

    for (const auto& konto : konta) {
        if (konto.size() < 4) continue; // Zabezpieczenie przed błędnymi liniami

        if (konto[0] == login && konto[1] == haslo) {
            string typ = konto[2];
            int id = stoi(konto[3]);

            if (typ == "czytelnik") {
                for (auto& c : czytelnicy) {
                    if (c.getId() == id) {
                        cout << "Zalogowano jako czytelnik!\n";
                        menuCzytelnika(c);
                        return;
                    }
                }
            }
            else if (typ == "pracownik") {
                for (auto& p : pracownicy) {
                    if (p.getId() == id) {
                        cout << "Zalogowano jako pracownik!\n";
                        menuPracownika(p);
                        return;
                    }
                }
            }
        }
    }
    cout << "Niepoprawny login lub haslo!\n";
}
int main() {
    simulatedCurrentDate = Date::getCurrentDate(); // Inicjalizacja symulowanej daty
    cout << "System biblioteczny uruchomiony." << endl;
    cout << "Aktualna data systemowa (rzeczywista): " << Date::getCurrentDate().to_string() << endl;
    cout << "Symulowana data (na starcie): " << simulatedCurrentDate.to_string() << endl;

    zaladujDane(); // Załaduj dane PO inicjalizacji daty
    int wybor;
    do {
        cout << "\n--- BIBLIOTEKA --- (Symulowana data: " << simulatedCurrentDate.to_string() << ") ---\n"; // Wyświetl symulowaną datę
        cout << "1. Zaloguj\n";
        cout << "2. Zarejestruj\n";
        cout << "3. Symuluj Czas\n"; // NOWA OPCJA
        cout << "4. Wyjdz\n";      // Przesunięta opcja
        cout << "Wybor: ";
        // Lepsza obsługa błędów wejścia
        while (!(cin >> wybor)) {
            cout << "Nieprawidlowy wybor. Podaj numer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruj newline po liczbie

        if (wybor == 1) logowanie();
        else if (wybor == 2) rejestracja();
        else if (wybor == 3) symulujCzas(); // Wywołanie nowej funkcji
        else if (wybor == 4) cout << "Zamykanie programu...\n";
        else cout << "Nieznana opcja.\n";

    } while (wybor != 4); // Zaktualizowany warunek wyjścia
    return 0;
}