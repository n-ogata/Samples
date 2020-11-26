#include <cxxabi.h>

#include <memory>
#include <string>
#include <typeinfo>

std::string Demangle(const char* mangled_name)
{
    using namespace std;
    int status = 0;
    unique_ptr<char, decltype(&free)> spName(abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status), free);
    return spName.get();
}

std::string GetName(const std::type_info& ti)
{
    return Demangle(ti.name());
}

template< typename Type>
std::string GetName(const Type& /*type*/)
{
    return GetName(typeid(Type));
}

#include <iostream>

using namespace std;

struct A {};

namespace ns {

struct B {};

} // namespace ns

int main()
{
    struct C {};
    A a;
    ns::B b;
    C c;
    cout << GetName(a) << endl;
    cout << GetName(b) << endl;
    cout << GetName(c) << endl;

    cout << GetName(&a) << endl;
    cout << GetName(*&a) << endl;

    cout << GetName(typeid(A)) << endl;

}
