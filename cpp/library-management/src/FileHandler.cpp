#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include "Pracownik.h"
#include "Wypozyczenie.h"
#include "iostream"
using namespace std;
vector<Czytelnik> FileHandler::wczytajCzytelnikow() {
    vector<Czytelnik> czytelnicy_local; // Local vector
    ifstream file("czytelnicy.csv");
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku czytelnicy.csv" << endl;
        return czytelnicy_local;
    }
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, imie, nazwisko, email, data_waznosci_str, limit_str;
        getline(ss, id_str, ';');
        getline(ss, imie, ';');
        getline(ss, nazwisko, ';');
        getline(ss, email, ';');
        getline(ss, data_waznosci_str, ';');
        getline(ss, limit_str, ';');
        try {
            int id = stoi(id_str);
            Date data = Date::from_string(data_waznosci_str);
            int limit = stoi(limit_str);

            // Construct directly in the vector using arguments
            czytelnicy_local.emplace_back(id, imie, nazwisko, email);

            // Get the newly added reader (last element) and set card details
            Czytelnik& new_reader = czytelnicy_local.back();
            new_reader.setLimitKsiazek(limit);
            if (new_reader.getKartaBiblioteczna()) { // Check if card exists (constructor should create it)
                new_reader.getKartaBiblioteczna()->setDataWaznosci(data);
            } else {
                // This case implies the constructor failed to create the card, which shouldn't happen with make_unique
                cerr << "Ostrzezenie: Nie udalo sie uzyskac karty dla czytelnika ID: " << id << endl;
            }
            // czytelnicy.push_back(c); // Replace this way
        } catch (const std::invalid_argument& e) {
            cerr << "Blad konwersji (stoi/from_string) w linii (czytelnicy): " << line << " - " << e.what() << endl;
        } catch (const std::out_of_range& e) {
            cerr << "Blad konwersji (stoi - out of range) w linii (czytelnicy): " << line << " - " << e.what() << endl;
        }
    }
        return czytelnicy_local;
}


vector<Ksiazka> FileHandler::wczytajKsiazki() {
    vector<Ksiazka> ksiazki;
    ifstream file("ksiazki.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, tytul, autor, gatunek, opis, dostepnosc_str;
        getline(ss, id_str, ';');
        getline(ss, tytul, ';');
        getline(ss, autor, ';');
        getline(ss, gatunek, ';');
        getline(ss, opis, ';');
        getline(ss, dostepnosc_str, ';');

        Ksiazka k;
        k.setId(stoi(id_str));
        k.setTytul(tytul);
        k.setAutor(autor);
        k.setGatunek(gatunek);
        k.setOpis(opis);
        k.ustawDostepnosc(dostepnosc_str == "1");
        ksiazki.push_back(k);
    }
    return ksiazki;
}

vector<vector<string>> FileHandler::wczytajKonta() {
    vector<vector<string>> konta;
    ifstream file("konta.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string login, haslo, typ, id;
        vector<string> konto;
        getline(ss, login, ';');
        getline(ss, haslo, ';');
        getline(ss, typ, ';');
        getline(ss, id, ';');
        konto = {login, haslo, typ, id};
        konta.push_back(konto);
    }
    cout << "Wczytano " << konta.size() << " kont z pliku\n";
    return konta;
}

void FileHandler::zapiszCzytelnikow(const vector<Czytelnik>& czytelnicy) {
    ofstream file("czytelnicy.csv");
    for (const auto& c : czytelnicy) {
        file << c.getId() << ";"
             << c.getImie() << ";"
             << c.getNazwisko() << ";"
             << c.getEmail() << ";"
             << c.getDataWaznosci().to_string() << ";"
             << c.getLimitKsiazek() << "\n";
    }
}

void FileHandler::zapiszKsiazki(const vector<Ksiazka>& ksiazki) {
    ofstream file("ksiazki.csv");
    for (const auto& k : ksiazki) {
        file << k.getId() << ";"
             << k.getTytul() << ";"
             << k.getAutor() << ";"
             << k.getGatunek() << ";"
             << k.getOpis() << ";"
             << (k.sprawdzCzyMoznaWypozyczyc() ? "1" : "0") << "\n";
    }
}

void FileHandler::zapiszKonto(const string& login, const string& haslo, const string& typ, int id) {
    ofstream file("konta.csv", ios::app);
    file << login << ";" << haslo << ";" << typ << ";" << id << "\n";
}
// FileHandler.cpp - dodane funkcje dla pracowników
vector<Pracownik> FileHandler::wczytajPracownikow() {
    vector<Pracownik> pracownicy;
    ifstream file("pracownicy.csv");

    if (!file.is_open()) {
        cerr << "Brak pliku pracownicy.csv! Tworze pusty." << endl;
        ofstream new_file("pracownicy.csv");
        return pracownicy;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, imie, nazwisko, email;
        getline(ss, id_str, ';');
        getline(ss, imie, ';');
        getline(ss, nazwisko, ';');
        getline(ss, email, ';');

        Pracownik p;
        p.setId(stoi(id_str));
        p.setImie(imie);
        p.setNazwisko(nazwisko);
        p.setEmail(email);
        pracownicy.push_back(p);
    }
    return pracownicy;
}

void FileHandler::zapiszPracownikow(const vector<Pracownik>& pracownicy) {
    ofstream file("pracownicy.csv");
    for (const auto& p : pracownicy) {
        file << p.getId() << ";"
             << p.getImie() << ";"
             << p.getNazwisko() << ";"
             << p.getEmail() << "\n";
    }
}
vector<Wypozyczenie> FileHandler::wczytajWypozyczenia() {
    vector<Wypozyczenie> wypozyczenia_local; // Use a different name to avoid confusion with global
    ifstream file("wypozyczenia.csv"); // Assuming getPath isn't strictly needed if files are local

    if (!file.is_open()) {
         cerr << "Blad: Nie mozna otworzyc pliku wypozyczenia.csv" << endl;
         return wypozyczenia_local; // Return empty vector
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;

        while (getline(ss, field, ';')) {
            fields.push_back(field);
        }

        // Expect exactly 4 fields now
        if (fields.size() == 4) {
            try {
                int idKsiazki = stoi(fields[0]);
                int idCzytelnika = stoi(fields[1]);
                Date dataWyp = Date::from_string(fields[2]);
                Date dataZwr = Date::from_string(fields[3]); // Read the saved return date

                // Use the new constructor
                wypozyczenia_local.emplace_back(idKsiazki, idCzytelnika, dataWyp, dataZwr);
            } catch (const std::invalid_argument& e) {
                 cerr << "Blad konwersji (stoi) w linii (wypozyczenia): " << line << " - " << e.what() << endl;
            } catch (const std::out_of_range& e) {
                 cerr << "Blad konwersji (stoi - out of range) w linii (wypozyczenia): " << line << " - " << e.what() << endl;
            }
             // Potentially add more specific error handling for Date::from_string if it can throw
        } else {
            cerr << "Ostrzezenie: Zignorowano nieprawidlowa linie w wypozyczenia.csv: " << line << endl;
        }
    }
    return wypozyczenia_local;
}

void FileHandler::zapiszWypozyczenia(const vector<Wypozyczenie>& wypozyczenia) {
    ofstream file(getPath("wypozyczenia.csv"));
    for (const auto& w : wypozyczenia) {
        file << w.getIdKsiazki() << ";"
             << w.getIdCzytelnika() << ";"
             << w.getDataWypozyczenia().to_string() << ";"
             << w.getDataZwrotu().to_string() << "\n";
    }

}
vector<Rezerwacja> FileHandler::wczytajRezerwacje() {
    vector<Rezerwacja> rezerwacje;
    ifstream file("rezerwacje.csv");

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;

        while (getline(ss, field, ';')) {
            fields.push_back(field);
        }

        if (fields.size() >= 4) {
            int id = stoi(fields[0]);
            int idKsiazki = stoi(fields[1]);
            int idCzytelnika = stoi(fields[2]);
            Date data = Date::from_string(fields[3]);
            rezerwacje.emplace_back(id, idKsiazki, idCzytelnika, data);
        }
    }
    return rezerwacje;
}

void FileHandler::zapiszRezerwacje(const vector<Rezerwacja>& rezerwacje) {
    ofstream file("rezerwacje.csv");  // <--- Add missing file declaration
    for (const auto& r : rezerwacje) {
        file << r.getId() << ";"
             << r.getIdKsiazki() << ";"
             << r.getIdCzytelnika() << ";"
             << r.getDataRezerwacji().to_string() << "\n";
    }
}
std::string FileHandler::getPath(const std::string& filename) {
    return base_path + filename;
}
std::string FileHandler::base_path = "";
