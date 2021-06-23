#include <vector>
#include "Parser.h"
#include "Reader.h"
#include "Writer.h"
#include "utils.h"


class Interpreter
{
    std::vector<Symbol> symbols;
    void interpret(const std::vector<Symbol>&);
    public:
    explicit Interpreter(std::vector<Symbol>);
    DBFile interpret();
};
