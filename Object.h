#pragma once
#include "typedefs.h"
#include "Cell.h"


class Object
{
    int size;
    Cell** data_begin;
    Cell** data_end;

    public:
    Object(int, Cell*, Cell*);
    int get_size() const { return size; }

    Cell** get_data() const;
    byte* get_data_bytes() const;
};


bool operator==(const Object&, const Object&);
