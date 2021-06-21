#include "Shell.h"


std::vector<std::string> Shell::split_args(std::string line)
{
    std::vector<std::string> args;
    short pos = 0;
    while ((pos = line.find(' ')) != std::string::npos) {
        args.push_back(line.substr(0, pos));
        line.erase(0, ++pos);
    }

    return args;
}


Shell::Shell()
{
    std::cout << "~~~~~~~~~~~ START OF MIDB SHELL ~~~~~~~~~~~" << std::endl;
    while (1)
    {
        char* inp;
        std::cout << "MIDB <<< ";
        std::cin >> inp;
        std::string line(inp);

        if (line == std::string("exit")) break;

        std::vector<std::string> args = split_args(line);
        for (std::string str : args)
        {
            std::cout << "------------ " << str << std::endl;
        }
    }
    std::cout << "~~~~~~~~~~~~ END OF MIDB SHELL ~~~~~~~~~~~~" << std::endl;
}
