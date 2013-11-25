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
    Logger(ostream& os, const string& prompt)
        : os_(os), prompt_(prompt)
    {}
    
private:
    ostream&    os_;
    string      prompt_;
    
public:
    template <typename T>
    ostream& operator<<(const T& x)
    {
        return os_ << prompt_ << x;
    }
};

static Logger mycerr(std::cerr, utils::boldface("[OKSHELL]  "));

} // end namespace detail
} // end namespace okshell

#endif /* LOGGER_H_ */
