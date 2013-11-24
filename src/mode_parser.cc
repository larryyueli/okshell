/*
 * mode_parser.cc
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#include "mode_parser.h"
#include <stdexcept>
#include "utils.h"

namespace okshell
{
namespace detail
{
using utils::lowercase;

MainMode ModeParser::parse(const vector<string>& args, 
        vector<string>& remaining_args) const
{
    remaining_args = vector<string>{};
    if (args.empty())
        throw std::runtime_error("ModeParser::parse, args is empty");
    else if (args.size() == 1)
    {
        return MainMode::EMPTY;
    }
    else if (args.size() == 2 && lowercase(args[1]) == "help")
    {
        // "ok help" is the same as "ok"
        return MainMode::EMPTY;
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

} // end namespace detail
} // end namespace okshell
