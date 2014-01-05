/*
 * mode_parser.cc
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

#include "mode_parser.h"

#include "utils.h"

namespace okshell
{
using std::string;
using std::vector;
using utils::lowercase;

MainMode ModeParser::parse(const vector<string>& args, 
        vector<string>& remaining_args) const
{
    remaining_args = vector<string>{};
    if (args.empty())
        throw OkShellException("ModeParser::parse, args is empty");
    else if (args.size() == 1)
    {
        return MainMode::EMPTY;
    }
    else if (args.size() == 2 && lowercase(args[1]) == "help")
    {
        // "ok help" is the same as "ok"
        return MainMode::HELP;
    }
    else if (lowercase(args[1]) == "ok")
    {
        remaining_args = vector<string>(args.begin() + 2, args.end());
        return MainMode::CONFIG;
    }
    else
    {
        remaining_args = vector<string>(args.begin() + 1, args.end());
        return MainMode::NORMAL;
    }
    return MainMode::ERROR;
}

} // end namespace okshell

