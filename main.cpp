#include <iostream>
#include <string>
#include <vector>
#include "errors.h"
#include "test/unit_tests.h"
#include "test/benchmarks.h"
#include "utils.h"
#include "Shell.h"
#include "Parser.h"
#include "Linker.h"
#include "Interpreter.h"


void run() {}


int main(int argc, char* argv[])
{
    std::string* args = new std::string[argc];
    for (char i = 0; i < argc; i++)
        args[i] = std::string(argv[i]);

    try
    {
        if (argc > 1)
        {
            if (args[1] == std::string("test"))
                unit_tests();
            else if (args[1] == std::string("benchmark") || args[1] == std::string("bm"))
                benchmarks();
            else if (args[1] == std::string("run"))
                run();
            else if (args[1] == std::string("shell"))
                Shell();
            else throw new CMDLineError("invalid cmd line argument", argv[1]);
        }
    }
    catch (BaseError* e)
    {
        std::cout << *e << std::endl;
    }
}
