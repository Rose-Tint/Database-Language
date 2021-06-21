#pragma once
#include <ios>
#include <fstream>
#include "Cell.h"
#include "Object.h"
#include "Column.h"
#include "Table.h"
#include "Metadata.h"
#include "typedefs.h"


class Writer
{
    std::string filename;
    std::ofstream bout;
    static constexpr std::ios::openmode openmode = std::ios::out | std::ios::binary;

    template<class T> void write(T, bool = false);

    public:
    Writer(std::string fname) : filename(fname) {}
    void write_fmd(const Metadata);
    void write(const Table, bool = false);
};
