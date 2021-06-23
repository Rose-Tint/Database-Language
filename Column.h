#pragma once
#include <string>
#include "Cell.h"
#include "typedefs.h"


enum Properties : u8
{
    nullable = 1 << 0,
    unique   = 1 << 1,
    primary  = 1 << 2,
    foreign  = 1 << 3
};


struct ColumnMetadata
{
    s8 name[16];
    u8 size;
    u8 properties;
};


bool operator==(const ColumnMetadata& left, const ColumnMetadata& right);


class Column
{
    ColumnMetadata metadata;
    Properties properties;

    public:
    static constexpr size_t md_size = sizeof(ColumnMetadata);

    Column(ColumnMetadata);
    Column(char*, u8, Properties);

    ColumnMetadata get_md() const { return metadata; }
    std::string get_name() const;
    unsigned get_size() const { return metadata.size; }
    Properties get_properties() const { return properties; }

    Cell create_cell() const { return Cell(metadata.size); };
    Cell create_cell(byte*) const;
};
