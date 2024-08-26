#pragma once

#include <iostream> 

// eventually want to be able to override this in the build so that the logging can be integrated with existing logs in pre-existing apps
// for now just wrap everything in begin and end macros

//TRACE << blah << ENDL;

namespace dsy
{

// a global spot for all my classes to look for verbose setting,
// instead of having to pass it into each class

class logs
{
public:
    inline uint32_t verbose = 0;

}; // end of logs

}; // end of namespace

#define TRACE std::cerr << get_nanoseconds() << ' ' << __func__ << ' ' << __FILE__ << ':' << __LINE__ << ' '
#define ENDL std::endl
