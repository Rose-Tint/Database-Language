#include "Object.h"
#include <iostream>


// Time: O(s)
// Space: O(1)
// where s = size
bool operator==(const Object& left, const Object& right)
{
    bool size = (left.get_size() == right.get_size());
    if (!size) return false;

    bool data = true;
    Cell** l_data = left.get_data();
    Cell** r_data = right.get_data();
    for (int i = 0; i < left.get_size(); i++)
        data &= (l_data[i] == r_data[i]);

    return size && data;
}


// Time: O(s)
// Space: O(1)
// where s = size
Object::Object(int _size, Cell* begin) : size(_size)
{
    data = new Cell*[size];
    for (int i = 0; i < size; i++)
        *(data + i) = begin + i;
}


// Time: O(1)
// Space: O(1)
Cell** Object::get_data() const { return data; }


// Time: O(s*w)
// Space: O(s*w)
// where s = size and w = the sum of the obj's cell's sizes
byte* Object::get_data_bytes() const
{
    int width;
    for (Cell** cell = data; cell < data + size; cell++)
        width += (*cell)->size;

    byte* bytes = new byte[width];
    for (int i = 0; i < size; i++)
    {
        byte* value = (*(data + i))->get_value();
        for (int j = 0; j < (*(data + i))->size; j++)
            *(bytes + j) = *(value + j);
    }

    return bytes;
}


// Time: O(1)
// Space: O(1)
Object::~Object() { delete[] data; }
