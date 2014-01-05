/*
 * logger.h
 * The class to replace cerr and cout by adding prompt before message
 *
 * Copyright (C) 2013  Larry Yueli Zhang
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include <unistd.h> // TODO, OS-specific headers

#include "common_defs.h"
#include "utils.h"
#include "globals.h"

namespace okshell
{

class Logger
{
public:
    // os is a stream object such as cout and cerr
    // prompt is the prefix of each output line
    // delay_in_ms is the delay before displaying each output line
    Logger(std::ostream& os, const std::string& prompt, unsigned delay_in_ms=0)
        : os_(os), prompt_(prompt), delay_in_us_(delay_in_ms * 1000)
    {}
    
private:
    std::ostream&   os_;
    std::string     prompt_;
    unsigned        delay_in_us_;
    
public:
    template <typename T>
    std::ostream& operator<<(const T& x)
    {
        usleep(delay_in_us_);
        return os_ << prompt_ << x;
    }
};

static Logger mycerr(std::cerr, kPromptHeader, 50);

} // end namespace okshell

#endif /* LOGGER_H_ */
