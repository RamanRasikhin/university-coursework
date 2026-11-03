
#include <iostream>
using namespace std;

int Sudan(int n,int x,int y) {
  if (n == 0) {
    return x + y;
  }
 
  else if (y == 0) {
    return x;
  }
 
  return Sudan(n - 1, Sudan(n, x, y - 1), Sudan(n, x, y - 1) + y);
}

int main() {
    int n, x, y;
    cout << "Podaj n: ";
    cin >> n;
    cout << "Podaj x: ";
    cin >> x;
    cout << "Podaj y: ";
    cin >> y;
    cout << "Sudan("<<n<<", "<<x<< ", " <<y<< ")="<<Sudan(n,x,y)<<endl;
  return 0;
}