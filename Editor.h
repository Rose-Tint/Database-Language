#include <string>
#include <fstream>
#include "Cell.h"
#include "Object.h"
#include "Column.h"
#include "Table.h"
#include "Metadata.h"
#include "typedefs.h"


class Editor
{
    std::string filename;
    std::fstream bfile;

    public:
    Editor(std::string fname) : filename(fname) {}

    // deleters
    void del_table(const ushort&);
    void del_column(const ushort&, const ushort&);
    void del_object(const ushort&); // TODO: FIGURE THIS WHOLE THING OUT

    // rewriters
    void rewrite_fmd(const Metadata);
    void rewrite_table(const Table);
    void rewrite_table(const Table, const ushort&);
    void rewrite_table(const Table, const std::string&);
};
