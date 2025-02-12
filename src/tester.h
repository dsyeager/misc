#pragma once

#include <iostream>
#include <source_location>
#include <string_view>

namespace tester
{

dsy::string_view function_name(std::string buff, const std::source_location loc = std::source_location::current())
{
    // tease a proper looking function name out of template syntax

    dsy::string_view fname = loc.function_name();
    fname = fname.after(' ');
    // test() [with NUMB = unsigned char; unsigned char BASE = 10]
    if (!fname.contains("[with "))
        return fname;

    buff = fname.before(" [");
    buff.push_back('<');
    dsy::string_view targs = fname.after("[with ").before(']');

    // loop split, split
    // NUMB = unsigned char; unsigned char BASE = 10
    while (!targs.empty())
    {
        auto targ = targs.split(';').after('=').ltrim(' ');
        buff.append(targ);
        buff.push_back(',');
        buff.push_back(' ');
    }
    buff.pop_back();
    buff.pop_back();
    buff.push_back('>');
    return buff;
}

class tester_obj
{   
public:
    tester_obj()
    {}

    ~tester_obj()
    {
        std::cout << "Test cnt: " << test_cnt << std::endl;
        std::cout << "Failure cnt: " << fail_cnt << std::endl;
    }

    void fail()
    {
        test_cnt++;
        sub_test_cnt++;
        fail_cnt++;
        sub_fail_cnt++;
    }

    void succeed()
    {
        test_cnt++;
        sub_test_cnt++;
    }

    void zero_sub()
    {
        sub_test_cnt = 0;
        sub_fail_cnt = 0;
    }

    int tests() const { return test_cnt; }
    int fails() const { return fail_cnt; }

    int sub_tests() const { return sub_test_cnt; }
    int sub_fails() const { return sub_fail_cnt; }

    int test_cnt = 0;
    int fail_cnt = 0;

    int sub_test_cnt = 0;
    int sub_fail_cnt = 0;
    bool show_success = false;
    std::string buff;
};  

static tester_obj s_test_obj; 

void show_success(bool val) { s_test_obj.show_success = val; }
void zero_sub() { s_test_obj.zero_sub(); }
int  sub_tests() { return s_test_obj.sub_tests(); }
int  sub_fails() { return s_test_obj.sub_fails(); }
    
bool check_equals(auto left, auto right, std::string_view desc, const std::source_location loc = std::source_location::current())
{
    if (left != right)
    {
        std::cerr << "FAILED, " << function_name(s_test_obj.buff, loc) 
                  << ", line: " << loc.line() 
                  << ", " << left << " != " << right 
                  << ", " << desc << std::endl;
        s_test_obj.fail();
        return false;
    }
    else if (s_test_obj.show_success)
    {
        std::cerr << "SUCCESS, " << function_name(s_test_obj.buff, loc) 
                  << ", line: " << loc.line() 
                  << ", " << left << " == " << right 
                  << ", " << desc << std::endl;
    }
    s_test_obj.succeed();
    return true;
}

bool check_is_true(bool val, std::string_view desc, const std::source_location loc = std::source_location::current())
{
    if (!val)
    {
        std::cerr << "FAILED, " << loc.function_name() << ", line: " << loc.line() << ", !true, " << desc << std::endl;
        s_test_obj.fail();
        return false;
    }
    else if (s_test_obj.show_success)
    {
        std::cerr << "SUCCESS, " << loc.function_name() << ", line: " << loc.line() << ", true, " << desc << std::endl;
    }
    s_test_obj.succeed();
    return true;
}

} // end namespace
