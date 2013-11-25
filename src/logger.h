/*
 * logger.h
 * The class to replace cerr and cout by adding prompt before message
 *
 *  Created on: 2013-11-25
 *      Author: Larry Yueli Zhang
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include <unistd.h>
#include "common_defs.h"
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::ostream;
using std::string;

class Logger
{
public:
    // os is a stream object such as cout and cerr
    // prompt is the prefix of each output line
    // delay_in_ms is the delay before displaying each output line
    Logger(ostream& os, const string& prompt, unsigned delay_in_ms=0)
        : os_(os), prompt_(prompt), delay_in_us_(delay_in_ms * 1000)
    {}
    
private:
    ostream&    os_;
    string      prompt_;
    unsigned    delay_in_us_;
    
public:
    template <typename T>
    ostream& operator<<(const T& x)
    {
        usleep(delay_in_us_);
        return os_ << prompt_ << x;
    }
};

static Logger mycerr(std::cerr, utils::boldface("[OKSHELL]  "), 100);

} // end namespace detail
} // end namespace okshell

#endif /* LOGGER_H_ */
