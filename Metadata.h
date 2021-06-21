#pragma once
#include "typedefs.h"


struct Metadata
{
    s8 signature[4];
    u8 table_count;
    u8 version;
    u32 changes;
};
