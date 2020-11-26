#include <bits/stdc++.h>

using namespace std;

int conv8(unsigned int v)
{
    constexpr auto over = 0x80;
    return v < over ? v : v - over * 2;
}

int conv16(unsigned int v)
{
    constexpr auto over = 0x8000;
    return v < over ? v : v - over * 2;
}

int main()
{
    {
        constexpr auto v = 127;
        const auto u8 = static_cast<unsigned int>(static_cast<unsigned char>(v));
        const auto i8 = static_cast<  signed int>(static_cast<  signed char>(v));
        cout << u8;
        cout << ' ';
        cout << i8;
        cout << ' ';
        cout << conv8(u8);
        cout << endl;
    }
    {
        constexpr auto v = 128;
        const auto u8 = static_cast<unsigned int>(static_cast<unsigned char>(v));
        const auto i8 = static_cast<  signed int>(static_cast<  signed char>(v));
        cout << u8;
        cout << ' ';
        cout << i8;
        cout << ' ';
        cout << conv8(u8);
        cout << endl;
    }
    {
        constexpr auto v = 255;
        const auto u8 = static_cast<unsigned int>(static_cast<unsigned char>(v));
        const auto i8 = static_cast<  signed int>(static_cast<  signed char>(v));
        cout << u8;
        cout << ' ';
        cout << i8;
        cout << ' ';
        cout << conv8(u8);
        cout << endl;
    }
    {
        constexpr auto v = 32767;
        const auto u16 = static_cast<unsigned short>(v);
        const auto i16 = static_cast<  signed short>(v);
        cout << u16;
        cout << ' ';
        cout << i16;
        cout << ' ';
        cout << conv16(u16);
        cout << endl;
    }
    {
        constexpr auto v = 32768;
        const auto u16 = static_cast<unsigned short>(v);
        const auto i16 = static_cast<  signed short>(v);
        cout << u16;
        cout << ' ';
        cout << i16;
        cout << ' ';
        cout << conv16(u16);
        cout << endl;
    }
    {
        constexpr auto v = 65535;
        const auto u16 = static_cast<unsigned short>(v);
        const auto i16 = static_cast<  signed short>(v);
        cout << u16;
        cout << ' ';
        cout << i16;
        cout << ' ';
        cout << conv16(u16);
        cout << endl;
    }
}
