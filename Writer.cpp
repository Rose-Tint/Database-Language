#include "Writer.h"


using std::ios;


template<class T>
void Writer::write(T data, bool close)
{
    bout.open(filename, bout.out | bout.binary);
    bout.write(reinterpret_cast<char*>(&data), sizeof(data));
    bout.close();
}


void Writer::write(const Table table, bool append)
{
    ios::openmode mode = (append) ? openmode | std::ios_base::ate : openmode;
    bout.open(filename, mode);

    write(table.get_md());
    for (Column col : table.get_columns())
        write(col.get_md());
    for (const Object& obj : table.get_objects())
    {
        byte* begin = obj.get_data_bytes();
        byte* end = obj.get_data_bytes() + obj.get_size();
        for (byte* bit = begin; bit < end; bit++)
            bout.put(*bit);
    }

    bout.close();
}
