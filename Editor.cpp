#include "Editor.h"


// Time: O()
// Space: O()
// where 
void Editor::del_table(const ushort& table_i)
{
    using std::ios;
    ios::openmode mode = bfile.in | bfile.out | bfile.binary;
    bfile.open(filename, mode);

    bfile.seekp(sizeof(Metadata));
    ulong i = 0;
    for (uint j = 0; j < table_i; j++)
    {
        ios::seekdir dir = ios::cur;
        ulong seek = sizeof(Metadata);
        seek += 1;
        bfile.seekp(seek, dir);
    }

    bfile.close();
}
