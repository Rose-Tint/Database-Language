#include "errors.h"


using std::string;


CMDLineError::CMDLineError(string msg, string g_arg) 
    : BaseError(msg), arg(g_arg) {}


FileError::FileError(string msg, string fname)
    : BaseError(msg), filename(fname) {}


ParserError::ParserError(string msg, string fname, string code_l, int ln, short col)
    : FileError(msg, fname), line(ln), column(col), code(code_l) {}


ReadError::ReadError(string msg, string fname, u16 i)
    : FileError(msg, fname), index(i) {}


std::ostream& CMDLineError::print(std::ostream& out) const
{
    out << "\033[1;31mCMDLineError: \033[0;1;36m" << message
        << "\n\033[0;34mArgument: " << arg;
    return out;
}


std::ostream& ReadError::print(std::ostream& out) const
{
    out << "\033[1;31mReadError \033[0;34m[at index "
        << index << ("]: \033[1;36m") << message;
    return out;
}


std::ostream& ParserError::print(std::ostream& out) const
{
    string squigles(code.size(), '~');
    squigles[column] = '^';
    out << "\033[0;34m" << code << "\033[0m\n\033[32m"
        << squigles << "\033[0m\n"
        << "\033[1;31mParserError \033[4;34mat line "
        << std::to_string(line + 1) << ": column "
        << std::to_string(column) << "\033[0;31m:\n\033[36m"
        << message;
    return out;
}
