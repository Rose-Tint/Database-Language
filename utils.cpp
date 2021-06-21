#include <stdlib.h>
#include "utils.h"


std::string get_envvar(std::string name, std::string def)
{
    std::string envvar = std::getenv(name.data());
    if (envvar.empty())
        envvar = def;
    return envvar;
}
