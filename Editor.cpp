#include "Editor.h"


void Editor::del_table(const ushort& table_i)
{
    using std::ios_base;
    std::ios_base::openmode mode = bfile.in | bfile.out | bfile.binary;
    bfile.open(filename, mode);

    bfile.seekp(sizeof(Metadata));
    ulong i = 0;
    for (uint j = 0; j < table_i; j++)
    {
        ios_base::seekdir dir = ios_base::cur;
        ulong seek = sizeof(Metadata);
        seek += 1;
        bfile.seekp(seek, dir);
    }

    bfile.close();
}
