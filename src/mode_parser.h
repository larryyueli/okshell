/*
 * mode_parser.h
 * Parser used to determine whether it is normal or special mode
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

#ifndef MODE_PARSER_H_
#define MODE_PARSER_H_

#include <string>
#include <vector>

#include "common_defs.h"

namespace okshell
{
using std::string;
using std::vector;

enum class MainMode
{
    ERROR=0, EMPTY, NORMAL, CONFIG, HELP
};
    
class ModeParser
{
public:
    ModeParser() {}
    
public:
    // return the working mode for the command, i.e., NORMAL or CONFIG
    // or just display help
    // Also, perform preprocessing and put clean result in remaining_args
    // Note that multiple words in quote signs are already in the same entry
    MainMode parse(const vector<string>& args, 
            vector<string>& remaining_args) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ModeParser);
};
} // end namespace okshell

#endif /* MODE_PARSER_H_ */
