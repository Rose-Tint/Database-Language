#include "Cell.h"
#include <iostream>


// Time: O(1) - O(s)
// Space: O(1)
// where s = size
bool operator==(const Cell& left, const Cell& right)
{
    bool size = (left.size == right.size);
    if (!size) return false;

    bool value = true;
    byte* l_val = left.get_value();
    byte* r_val = right.get_value();
    for (int i = 0; i < left.size; i++)
        value &= (l_val[i] == r_val[i]);

    return size && value;
}


// Time: O(s)
// Space: O(s)
// where s = size
Cell::Cell(unsigned _size) : size(_size)
{
    value = new byte[size];
    for (byte* val = value; val < value + size; val++)
        *val = 0;
}


// Time: O(s)
// Space: O(s)
// where s = size
Cell::Cell(unsigned _size, byte* begin) : size(_size)
{
    value = new byte[size];
    for (unsigned i = 0; i < size; i++)
        *(value + i) = *(begin + i);
}


// Time: O(1)
// Space: O(1)
byte* Cell::get_value() const { return value; }


// Time: O(1)
// Space: O(1)
Cell& Cell::operator=(Cell&&) { return *this; }


// Time: O(1)
// Space: O(1)
Cell& Cell::operator=(Cell&) { return *this; }


// Time: O(c)
// Space: O(1)
// where c = count
void Cell::set(byte* begin, unsigned count)
{
    for (int i = 0; i < count; i++)
        *(value + size - count + i) = *(begin + i);
}


// Time: O(1)
// Space: O(1)
void Cell::set(unsigned i, byte _byte) { *(value + i) = _byte; }


// Time: O(1)
// Space: O(1)
Cell::~Cell() { delete[] value; }
