#pragma once
#include "typedefs.h"


class Cell
{
    friend class Column;
    template<class> friend bool test();

    byte* value_begin;
    byte* value_end;

    public:
    const ushort size; // size in bytes of the value

    explicit Cell(unsigned);
    Cell(unsigned, byte*); // range constructor

    ~Cell();

    byte* get_value_begin() { return value_begin; }
    byte* get_value_end() { return value_end; }
    Cell& operator=(Cell&&);
    Cell& operator=(Cell&);
    byte* value() const;
    void set(byte*, byte*);
};


bool operator==(const Cell&, const Cell&);
