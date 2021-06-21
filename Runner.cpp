#include "Reader.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Writer.h"
#include "utils.h"


class Runner
{
    public:
    // enum opts
    // {
    //     new_db      = 1 << 0,
    //     existing_db = 1 << 1,
    // };
    void operator()(bool = false);
};


void Runner::operator()(bool existing_db)
{
    if (existing_db)
    {
        Reader* reader = new Reader(get_envvar("MIDB_DB_FILENAME"));
        DBFile db = reader->read();
    }
    else
    {
        Parser* parser = new Parser(get_envvar("MIDB_CODE_FILENAME"));
        std::vector<Symbol> symbols = parser->parse();
        delete parser;

        Interpreter* intrptr = new Interpreter(symbols);
        DBFile db = intrptr->interpret();
        delete intrptr;
    }
}
