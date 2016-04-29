#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "Defines.h"
typedef unsigned char BYTE;

namespace iceberg
{
    namespace utility
    {
     /* Helper functions */
        // Reads a file in as a vector of unsigned chars (bytes)
        ICEBERGAPI std::vector<BYTE> ReadAllBytes(const std::string& filename);       
    }
}

#endif