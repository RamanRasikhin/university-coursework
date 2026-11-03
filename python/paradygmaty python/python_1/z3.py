student_oceny = {
    "Matematyka": [3, 5, 4, 2, 3],
    "Fizyka": [3, 2, 3, 5, 6, 4],
    "Wychowanie fizyczne": [4, 3, 5, 5, 5],
    "Polski jezyk": [3, 4, 5, 3, 4]
}

def srednia(lista_ocen):
    calosc = 0
    liczba_elementow = 0
    for element in lista_ocen:
        calosc += element
        liczba_elementow += 1
    if liczba_elementow == 0:
        return 0
    wynik = calosc / liczba_elementow
    return wynik

while True:
    print("\nMenu:")
    print("1. Dodaj ocenę")
    print("2. Wyświetl oceny z przedmiotu")
    print("3. Oblicz średnią z przedmiotu")
    print("4. Wyjdź")

    wybor = input("Wybierz opcję (1-4): ")

    if wybor == '1':
        przedmiot = input("Podaj nazwę przedmiotu: ")
        ocena = int(input("Podaj ocenę (1-6): "))
        if przedmiot not in student_oceny:
            student_oceny[przedmiot] = []
        student_oceny[przedmiot].append(ocena)
        print(f"Dodano ocenę {ocena} z przedmiotu {przedmiot}")

    elif wybor == '2':
        przedmiot = input("Podaj nazwę przedmiotu: ")
        oceny = student_oceny.get(przedmiot)
        if oceny:
            print(f"Oceny z {przedmiot}: {', '.join(map(str, oceny))}")
        else:
            print("Brak ocen dla tego przedmiotu")

    elif wybor == '3':
        przedmiot = input("Podaj nazwę przedmiotu: ")
        oceny = student_oceny.get(przedmiot)
        if oceny:
            sr = srednia(oceny)
            print(f"Średnia z {przedmiot}: {sr:.2f}")
        else:
            print("Brak ocen dla tego przedmiotu")

    elif wybor == '4':
        print("Koniec programu")
        break

    else:
        print("Nieprawidłowa opcja. Wybierz 1-4")