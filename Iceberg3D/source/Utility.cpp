#include "Utility.h"
#include <ios>
#include <iterator>
#include <fstream>

using namespace iceberg;
using namespace utility;

std::vector<BYTE> utility::ReadAllBytes(const std::string& filename)
{
    using namespace std;
    ifstream file(filename.c_str(), ios::binary | ios::ate);
    file >> noskipws;

    streampos fileSize = file.tellg();
    file.seekg(0, ios::beg);

    vector<BYTE> bytes;
    bytes.reserve(fileSize);

    copy(istream_iterator<BYTE>(file),
        istream_iterator<BYTE>(),
        back_inserter(bytes));

    return bytes;
}