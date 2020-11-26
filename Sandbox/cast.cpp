#include <bits/stdc++.h>

using namespace std;

int main()
{
    //uint32_t value;
    //cin >> value;
    //cout << *static_cast<float*>(static_cast<void*>(&value)) << endl;
    union Cast {
        uint32_t u32;
        float    f32;
    };
    union Cast cast;
    cin >> cast.u32;
    cout << cast.f32 << endl;
    return 0;
}
