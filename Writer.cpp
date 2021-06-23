#include "Writer.h"


using std::ios;


// Time: O(k)
// Space: O(1)
template<class T>
void Writer::write(T data, bool close)
{
    bout.open(filename, bout.out | bout.binary);
    bout.write(reinterpret_cast<char*>(&data), sizeof(data)); // O(k)
    bout.close();
}


// Time: O(k+c+o)
// Space: O(o)
// where c = # columns and o = # objects in given table
void Writer::write(const Table table, bool append)
{
    ios::openmode mode = (append) ? openmode | ios::ate : openmode;
    bout.open(filename, mode);

    write(table.get_md());

    for (Column col : table.get_columns())
        write(col.get_md());

    for (const Object& obj : table.get_objects())
    {
        byte* begin = obj.get_data_bytes();
        for (byte* val = begin; val < begin + obj.get_size(); val++)
            bout.put(*val);
    }

    bout.close();
}
