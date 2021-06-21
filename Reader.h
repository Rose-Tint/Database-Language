#pragma once
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include "Cell.h"
#include "Object.h"
#include "Column.h"
#include "Table.h"
#include "Metadata.h"
#include "errors.h"
#include "typedefs.h"


struct DBFile
{
    Metadata metadata;
    std::vector<Table> tables;
};


class Reader
{
    std::string filename;
    std::ifstream bin;
    static constexpr std::ios::openmode openmode = std::ios::in | std::ios::binary;
    void open();

    template<class T> T read_t(bool = false);
    template<class T> void skip_t();

    Table read_tbl();

    public:
    Reader(std::string fname) : filename(fname) {}

    Metadata read_fmd(bool = false);
    Table read_tbl(const unsigned&);
    DBFile read();
};
