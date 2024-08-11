#pragma once

#include "get_nanoseconds.h"

#include <string_view>
#include <vector>

/**
 Helper class for checking how long the different serial parts of an app are taking
 Intended for use in the main thread at a high level. It does not aggregate multiple calls for the same desc.
 So try not to use it in a re-entrant function.
 This is not meant to get the timings for individual functions. It relies on the times being sequential.
 It is appending to a vector each time add_time() is called so be aware of memory usage.

 int main()
 {
    // do some initialization logic
    times::add("initialized"sv);

    // read some files, parse data
    times::add("data read"sv);

    // resolve remote server addresses
    times::add("servers resolved"sv);

    // connect to the remote servers
    times::add("connected"sv);

    // send data
    times::add("data sent"sv);

    // receive data
    times::add("data received and processed"sv);

    // persist state
    times::add("state persisted"sv);

    // we are done
    times::show();
 */

namespace dsy
{

class times
{
public:
    static void add(const std::string_view &desc)
    {
        times::s_times_vector.push_back(std::make_pair(desc, get_nanoseconds()));
    }

    static void show()
    {
        uint64_t prev = 0;

        // TODO: consider adding an optional aggregation step for apps that call
        // add_time repeatedly for the same desc.

        for (auto & [key, val] : times::s_times_vector)
        {
            auto &pr = s_times[i];
            std::cout << key << ": ";
            if (prev)
                std::cout << (double(val - prev) / 1000);
            else
                std::cout << 0;
            std::cout << " us" << std::endl;
            prev = val;
        }
    }

private:
    static std::vector<pair<std::string_view, uint64_t>> s_times_vector;
}; // end times class

}; // end namespace dsy
