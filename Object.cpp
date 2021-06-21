#include "Object.h"
#include <iostream>


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


Object::Object(int _size, Cell* begin, Cell* end) : size(_size)
{
    data_begin = new Cell*[size];
    data_end = data_begin + size;
    
    for (Cell** cell = data_begin; cell < data_end; cell++)
        **cell = *(begin + size);
}


Cell** Object::get_data() const
{
    return data_begin;
}


byte* Object::get_data_bytes() const
{
    int width;
    for (Cell** cell = data_begin; cell < data_end; cell++)
        width += (*cell)->size;

    byte* data = new byte[width];
    byte* data_ptr = data;
    for (Cell** cell = data_begin; cell < data_end; cell++)
    {
        byte* begin = (*cell)->value();
        byte* end = begin + (*cell)->size;
        for (byte* bit = begin; bit < end; bit++)
            *(data_ptr++) = *bit;
    }

    return data;
}
