#include <iostream>

int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

int main() {
    int m, n;
    std::cout << "Podaj wartosc m: ";
    std::cin >> m;
    std::cout << "Podaj wartosc n: ";
    std::cin >> n;
    int result = ackermann(m, n);
    std::cout << "Wynik funkcji Ackermanna dla m = " << m << " i n = " << n << " to " << result << std::endl;
    return 0;
}
