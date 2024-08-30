#pragma once

#include <string.h>

#include <iostream> 
#include <mutex> 

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
    inline static uint32_t verbose = 0;

}; // end of logs

}; // end of namespace

inline std::mutex s_log_mutex;

#define TRACE(level) if (dsy::logs::verbose >= level) { std::unique_lock alock(s_log_mutex); std::cerr << get_nanoseconds() << " TRACE " << __func__ << ' ' << basename(__FILE__) << ':' << __LINE__ << ' '
#define ERROR { std::unique_lock alock(s_log_mutex); std::cerr << get_nanoseconds() << " ERROR " << __func__ << ' ' << basename(__FILE__) << ':' << __LINE__ << ' '
#define ENDL std::endl; }

