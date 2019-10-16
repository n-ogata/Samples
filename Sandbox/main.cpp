#include <bits/stdc++.h>

using namespace std;

void sub()
{
    for (auto x = -50; x <= 50; x += 100) {
        for (auto y = -15; y <= 15; y += 30) {
            for (auto z = -20; z <= 20; z += 40) {
                cout << x << ", " << y << ", " << z << endl;
            }
        }
    }
}

int main()
{
    sub();
    return 0;
}
