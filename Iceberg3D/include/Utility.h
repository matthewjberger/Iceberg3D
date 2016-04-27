#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "Defines.h"
typedef unsigned char BYTE;

namespace iceberg
{
    /* Helper functions */
    class ICEBERGAPI Utility
    {
    public:
        // Reads a file in as a vector of unsigned chars (bytes)
        static std::vector<BYTE> ReadAllBytes(const std::string& filename);
    };
}

#endif