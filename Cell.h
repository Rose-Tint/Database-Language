#pragma once
#include "typedefs.h"


class Cell
{
    friend class Column;

    byte* value;

    public:
    const ushort size; // size in bytes of the value

    explicit Cell(unsigned);
    Cell(unsigned, byte*); // range constructor
    Cell& operator=(Cell&&);
    Cell& operator=(Cell&);

    ~Cell();

    byte* get_value() const;

    void set(byte*, unsigned);
    void set(unsigned, byte);
};


bool operator==(const Cell&, const Cell&);
