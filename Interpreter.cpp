#include "Interpreter.h"


Interpreter::Interpreter(std::vector<Symbol> symbs) : symbols(symbs) {}


DBFile Interpreter::interpret()
{
    Writer* writer = new Writer(get_envvar("MIDB_DB_FILENAME"));

    DBFile dbf;
    return dbf;
}
