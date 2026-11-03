#include <iostream>
using namespace std;

int Sudan(int n, int x, int y, int& ackermannCalls) {
    cout << "Sudan(" << n << ", " << x << ", " << y << ") ";
    if (n == 0) {
        return x + y;
    }
 
    else if (y == 0) {

        return x;
    }
 
ackermannCalls++;
    return Sudan(n - 1, Sudan(n, x, y - 1, ackermannCalls), Sudan(n, x, y - 1, ackermannCalls) + y, ackermannCalls);
}

int main() {
    int n, x, y;
    cout << "Podaj n: ";
    cin >> n;
    cout << "Podaj x: ";
    cin >> x;
    cout << "Podaj y: ";
    cin >> y;

    int ackermannCalls = 0;
    cout << "Wynik: Sudan(" << n << ", " << x << ", " << y << ") = " << Sudan(n, x, y, ackermannCalls) << endl;
    cout << "Liczba pomocniczych wywolan funkcji Ackermanna: " << ackermannCalls << endl;

    return 0;
}
