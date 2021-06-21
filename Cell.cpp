#include "Cell.h"
#include <iostream>


bool operator==(const Cell& left, const Cell& right)
{
    bool size = (left.size == right.size);
    if (!size) return false;

    bool value = true;
    byte* l_val = left.value();
    byte* r_val = right.value();
    for (int i = 0; i < left.size; i++)
        value &= (l_val[i] == r_val[i]);

    return size && value;
}


Cell::Cell(unsigned _size) : size(_size)
{
    byte* temp_arr = new byte[size];
    value_begin = &temp_arr[0];
    value_end = &temp_arr[size - 1] + 1;

    for (byte* bit = value_begin; bit < value_end; bit++)
        *bit = 0;
}


Cell::Cell(unsigned _size, byte* begin, byte* end) : size(_size)
{
    value_begin = begin;
    value_end = end;
    set(begin, end);
}


byte* Cell::value() const { return value_begin; }


Cell& Cell::operator=(Cell&&) { return *this; }


Cell& Cell::operator=(Cell&) { return *this; }


void Cell::set(byte* begin, byte* end)
{
    for (byte* bit = value_begin; bit < value_end; bit++)
        *bit = *(begin++);
}
