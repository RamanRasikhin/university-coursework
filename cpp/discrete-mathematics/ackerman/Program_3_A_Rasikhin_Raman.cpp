#include <iostream>

int ackermann(int m, int n, int& call_count) {
    call_count++;
    std::cout << "A(" << m << ", " << n << ")" << std::endl;
    
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1, call_count);
    } else if (m > 0 && n > 0) {
        int temp = ackermann(m, n - 1, call_count);
        return ackermann(m - 1, temp, call_count);
    }
}

int main() {
    int m, n;
    std::cout << "Podaj wartosc m: ";
    std::cin >> m;
    std::cout << "Podaj wartosc n: ";
    std::cin >> n;
    
    int call_count = 0;
    int result = ackermann(m, n, call_count);
    
    std::cout << "Wynik funkcji Ackermanna dla m = " << m << " i n = " << n << " to " << result << std::endl;
    std::cout << "Liczba pomocniczych wywolan funkcji Ackermanna: " << call_count << std::endl;
    
    return 0;
}