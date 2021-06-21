#include "Linker.h"
/*

namespace fs = std::filesystem;


std::vector<fs::path>& Linker::find_paths()
{
    paths.clear();
    for (fs::directory_entry dir : fs::directory_iterator(home))
        if (dir.path().extension() == ext)
            paths.push_back(dir);
    return paths;
}


std::vector<std::vector<Symbol>>& Linker::get_all_symbols()
{
    symbols.clear();
    for (fs::path path : find_paths())
        symbols.push_back(Parser(path).parse());
    return symbols;
}
*/