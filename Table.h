#pragma once
#include <string>
#include <vector>
#include <map>
#include "typedefs.h"
#include "Object.h"
#include "Column.h"
#include "Cell.h"
#include "Metadata.h"


struct TableMetadata
{
    s8 name[16];
    u8 column_count;
    u16 object_count;
};


class Table
{
    TableMetadata metadata;
    std::map<std::string, Column> columns;
    std::vector<Object> objects;

    void add_column(const Column& col) { columns.insert({ col.get_name(), col }); }

    public:
    static constexpr size_t md_size = sizeof(TableMetadata);

    Table(TableMetadata, std::vector<Column>, std::vector<Object>);
    Table(TableMetadata, std::vector<Column>);

    TableMetadata get_md() const { return metadata; }
    std::string get_name() const;
    std::vector<Object> get_objects() const { return objects; }
    std::vector<Column> get_columns() const;

    Object create_object() const;
    void insert() { objects.push_back(create_object()); }
    void insert(const Object& obj) { objects.push_back(obj); }
};
