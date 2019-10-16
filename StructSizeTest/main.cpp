#include <iostream>

#include "sharedmemory_struct_template.h"

using namespace std;

int main(int argc, char* argv[])
{
    using TestData = sharedmemory::StructTmpl<12, 2>;

    cout << sizeof(TestData      ) << endl;
    cout << sizeof(TestData::data) << endl;

    cout << TestData::OneSize << endl;
    cout << TestData::Count   << endl;
    cout << TestData::Size    << endl;

    // Result
    // 24
    // 24
    // 12
    // 2
    // 24

    return 0;
}
