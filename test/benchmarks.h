#pragma once
#include <iostream>
#include <string>
#include "../typedefs.h"
#include "../Cell.h"
#include "../Column.h"
#include "../Table.h"


namespace cnstr
{
    namespace cell
    {
        constexpr unsigned size_b = 4; 
        void size();
        void range();
    }
}


void benchmark();
void benchmarks();
