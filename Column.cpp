#include "Column.h"


// Time: O(1)
// Space: O(1)
bool operator==(const ColumnMetadata& left, const ColumnMetadata& right)
{
    bool name = true;
    for (int i = 0; i < 16; i++)
        name &= (left.name[i] == right.name[i]);

    bool size = left.size == right.size;
    bool props = left.properties == right.properties;

    return (name && size && props);
}


// Time: O(1)
// Space: O(1)
Column::Column(ColumnMetadata cmd)
{
    metadata = cmd;
    properties = static_cast<Properties>(cmd.properties);
}


// Time: O(1)
// Space: O(1)
Column::Column(char* name, u8 size, Properties props) : properties(props)
{
    ColumnMetadata cmd =
    {
        {
            name[0],
            name[1],
            name[2],
            name[3],
            name[4],
            name[5],
            name[6],
            name[7],
            name[8],
            name[9],
            name[10],
            name[11],
            name[12],
            name[13],
            name[14],
            '\0'
        },
        size,
        static_cast<u8>(props)
    };

    metadata = cmd;
}


// Time: O(1)
// Space: O(1)
std::string Column::get_name() const
{ return std::string(reinterpret_cast<const char*>(metadata.name)); }


// Time: O(1)
// Space: O(1)
Cell Column::create_cell(byte* begin) const { return Cell(metadata.size, begin); }
