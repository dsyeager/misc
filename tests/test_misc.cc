#include "commas.h"

#include <charconv>
#include <climits>
#include <locale>
#include <source_location>
#include <iostream>
#include <sstream>
#include <string_view>

using std::string;
using namespace std::literals;

class tester
{
public:
    tester()
    : test_cnt(0), fail_cnt(0)
    {}
    ~tester()
    {
        std::cout << "Test cnt: " << test_cnt << std::endl;
        std::cout << "Failure cnt: " << fail_cnt << std::endl;
    }

    int test_cnt;
    int fail_cnt;
};
static tester test_obj;

void check_equals(auto left, auto right, std::string_view desc, const std::source_location loc = std::source_location::current())
{
    test_obj.test_cnt++;
    if (left != right)
    {
        std::cerr << "FAILED, " << loc.function_name() << ", line: " << loc.line() << ", " << left << " != " << right << ", " << desc << std::endl;
        test_obj.fail_cnt++;
    }
}

void test_commas()
{
    string buff1;
    string buff2;

    buff1 = add_commas(1000000U);
    buff2 = commas(1000000U);
    check_equals(buff1, buff2, "commas are correct"); 

    for (int32_t i = -1000000; i < 2000000; i += 5)
    {
        buff1 = add_commas(i);
        buff2 = commas(i);
        check_equals(buff1, buff2, "commas are correct"); 
    }
}

int main (int argc, char **argv)
{
    test_commas();
}
