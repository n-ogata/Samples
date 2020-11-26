#include <cstdint>
#include <iostream>

using namespace std;

union Value
{
    uint8_t  u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t   i8;
    int16_t  i16;
    int32_t  i32;
    float    f32;
    double   f64;
    uint8_t  ar[8];
};

ostream& operator<<(ostream& s, uint8_t c)
{
    s << static_cast<int>(c);
    return s;
}

ostream& operator<<(ostream& s, int8_t c)
{
    s << static_cast<int>(c);
    return s;
}

ostream& operator<<(ostream& s, uint8_t ar[8])
{
    s << hex << uppercase;
    for (auto i = 0u; i < 8; ++i) {
        s << '[' << ar[i] << ']';
    }
    return s;
}

int main()
{
    Value val{};
    //val.u64 = 0x4092491AA1636DDE;
    //val.u64 = 0xDE6D63A11A499240;
    //val.u16 = 0x74c2;
    //val.u16 = 0xc274;
    val.u16 = 0xb1e0;
    cout << "uint8_t  :" << val.u8  << endl;
    cout << "uint16_t :" << val.u16 << endl;
    cout << "uint32_t :" << val.u32 << endl;
    cout << "uint64_t :" << val.u64 << endl;
    cout << "int8_t   :" << val.i8  << endl;
    cout << "int16_t  :" << val.i16 << endl;
    cout << "int32_t  :" << val.i32 << endl;
    cout << "float    :" << val.f32 << endl;
    cout << "double   :" << val.f64 << endl;
    cout << "uint8_t[]:" << val.ar  << endl;
}
