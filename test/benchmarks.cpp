#include <ctime>
#include <chrono>
#include <utility>
#include "benchmarks.h"


namespace cnstr
{
    namespace cell
    {
        void size() { Cell c = Cell(size_b); }
        void range()
        {
            byte bytes[size_b] { 43, 79, 3, 19 };
            Cell cell(size_b, bytes, bytes + size_b);
        }
    }
}


template<typename F, typename ...Args>
void benchmark(const std::string msg, F func, Args ...args)
{
    using namespace std::chrono;
    using hsc = high_resolution_clock;
    using ms = milliseconds;

    static constexpr short count = 10000;

    std::cout << "\t\033[0;1;34m" << msg << "... \033[0;1;35m";

    double avg = 0;
    for (short i = 0; i < count; i++)
    {
        auto t1 = high_resolution_clock::now();
        function(std::forward<Args>(args)...);
        auto t2 = high_resolution_clock::now();

        duration<double, std::milli> current = t2 - t1;
        avg += current.count();
    }

    avg /= count;
    std::cout << std::to_string(avg) << std::endl;
}

void benchmarks()
{
    std::cout << "\033[0;33m~~~~~~~~~~~~ START OF BENCHMARKS ~~~~~~~~~~~~\033[0m\n" << std::endl;

    std::cout << "\033[0;1;36mCell:\033[0m" << std::endl;
    benchmark("size constructor", cnstr::cell::size);
    benchmark("range constructor", cnstr::cell::range);
    std::cout << std::endl;

    std::cout << "\033[0;1;36mColumn:\033[0m" << std::endl;
    std::cout << std::endl;

    std::cout << "\033[0;33m~~~~~~~~~~~~  END OF BENCHMARKS  ~~~~~~~~~~~~\033[0m" << std::endl;
}
