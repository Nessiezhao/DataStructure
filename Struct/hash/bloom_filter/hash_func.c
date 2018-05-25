#include <stdio.h>
#include<stddef.h>

size_t BKDRHash(const char* str)
{
    size_t hash = 0;
    while(size_t ch = (size_t)*str++)
    {
        hash = hash * 131 +ch;
    }
    return hash;
}
