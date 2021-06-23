#include "Reader.h"


// Time: O(1)
// Space: O(1)
// where 
void Reader::open()
{
    if (!bin.is_open())
        bin.open(filename, openmode);
    if (!bin.good())
    {
        std::string msg = "An error occurred while trying to open the file";
        throw ReadError(msg, filename, 0);
    };
}


// Time: O(t)
// Space: O(t)
// where t = # of tables
DBFile Reader::read()
{
    open();
    Metadata fmd = read_fmd();
    std::vector<Table> tables;
    for (short i = 0; i < fmd.table_count; i++)
        tables.push_back(read_tbl(i));
    return { fmd, tables };
}


// Time: O(1)
// Space: O(1)
template<class T>
T Reader::read_t(bool close)
{
    open();
    char* data = new char[sizeof(T)];
    bin.read(data, sizeof(T));
    if (close) bin.close();
    T T_data = *((T*)data);
    return T_data;
}


// Time: O(1)
// Space: O(1)
template<class T>
void Reader::skip_t() { bin.seekg(sizeof(T), bin.cur); }


// Time: O(c + o)
// Space: O(c)
// where c = # of columns and o = # of objs
template<>
void Reader::skip_t<Table>()
{
    TableMetadata table_md = read_t<TableMetadata>();
    std::vector<u16> sizes;

    for (ushort i = 0; i < table_md.column_count; i++)
        sizes.push_back(read_t<ColumnMetadata>().size);

    for (uint i = 0; i < table_md.object_count; i++)
        for (ushort j = 0; j < table_md.column_count; j++)
            for (uint k = 0; k < sizes[j]; k++)
                skip_t<byte>();
}


// Time: O(1)
// Space: O(1)
Metadata Reader::read_fmd(bool close)
{
    open();
    int old_seek = bin.tellg();
    bin.seekg(0, std::ios::beg);
    Metadata md = read_t<Metadata>(close);
    bin.seekg(old_seek, std::ios::beg);
    return md;
}


// Time: O()
// Space: O()
// where 
template<>
Table Reader::read_t<Table>(bool close)
{
    TableMetadata table_md = read_t<TableMetadata>();
    std::vector<Column> cols;

    for (ushort i = 0; i < table_md.column_count; i++)
    {
        ColumnMetadata col_md = read_t<ColumnMetadata>();
        std::string col_name(col_md.name, col_md.name + sizeof(col_md.name));
        Properties col_props = static_cast<Properties>(col_md.properties);
        cols.emplace_back(col_name.data(), col_md.size, col_props);
    }

    std::vector<Object> objects;
    for (uint i = 0; i < table_md.object_count; i++)
    {
        Cell* cells[table_md.column_count];
        for (ushort j = 0; j < table_md.column_count; j++)
        {
            const Column& col = cols[j];
            Cell* cell = cells[j];
            byte* data = new byte[col.get_size()];
            for (byte* _byte = data; _byte < data + col.get_size(); _byte++)
                *data = read_t<byte>();
            *cell = col.create_cell(data);
        }

        Cell* begin = *cells;
        Cell* end = *cells + table_md.column_count;
        objects.push_back(Object(table_md.column_count, begin));
    }

    if (close) bin.close();
    return Table(table_md, cols, objects);
}


// Time: O()
// Space: O()
// where 
Table Reader::read_tbl(const unsigned& table_i)
{
    open();
    Metadata fmd = read_fmd();
    if (table_i >= fmd.table_count)
    {
        std::string msg = "Table index given is greater than the number of Tables found";
        u16 index = -1;
        ReadError err(msg, filename, index);
        throw err;
    };

    for (ushort i = 0; i < fmd.table_count - 1; i++)
        skip_t<Table>();

    return read_t<Table>();
}
