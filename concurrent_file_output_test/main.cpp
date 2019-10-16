#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    string file_path("./concurrent_file_output_test.txt");
    try {
        ofstream os(file_path, ios::app);
        os.exceptions(ios::failbit);
        os << argv[1] << endl;
    } catch (const exception& ex) {
        cerr << "write error " << file_path << endl;
        return 1;
    }
    return 0;
}
