#include "Table.h"
#include <iostream>


Table::Table(TableMetadata md, std::vector<Column> cols, std::vector<Object> objs)
{
    objects = objs;
    metadata = md;
    for (Column col : cols)
        add_column(col);
}


Table::Table(TableMetadata md, std::vector<Column> cols)
{
    metadata = md;
    for (Column col : cols)
        add_column(col);
}


std::vector<Column> Table::get_columns() const
{
    std::vector<Column> cols;
    for (std::pair<std::string, Column> pair : columns)
        cols.push_back(pair.second);

    return cols;
}


std::string Table::get_name() const
{ return std::string(reinterpret_cast<const char*>(metadata.name)); }


Object Table::create_object() const
{
    Cell** cells = new Cell*[columns.size()];
    int i = 0;
    for (std::pair<std::string, Column> pair : columns)
        *cells[i++] = pair.second.create_cell();

    Cell* data_begin = *cells;
    Cell* data_end = *(cells + columns.size());
    return Object(columns.size(), data_begin, data_end);
}
