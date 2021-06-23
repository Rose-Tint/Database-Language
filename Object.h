#pragma once
#include "typedefs.h"
#include "Cell.h"


class Object
{
    int size; // number of cells
    Cell** data;

    public:
    explicit Object(int);
    Object(int, Cell*);

    ~Object();

    int get_size() const { return size; }
    Cell** get_data() const;
    byte* get_data_bytes() const;
};


bool operator==(const Object&, const Object&);
