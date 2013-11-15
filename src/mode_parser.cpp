/*
 * mode_parser.cpp
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#include "mode_parser.hpp"
#include <stdexcept>
#include "utils.hpp"

namespace okshell
{
namespace detail
{

mode_t ModeParser::parse(const vector<string>& args, vector<string>& remaining_args) const
{
    remaining_args = vector<string>{};
    if (args.empty())
        throw std::runtime_error("ModeParser::parse, args is empty");
    else if (args.size() == 1)
    {
        return mode_t::empty;
    }
    else if (args.size() == 2 && lowercase(args[1]) == "help")
    {
        // "ok help" is the same as "ok"
        return mode_t::empty;
    }
    else if (lowercase(args[1]) == "ok")
    {
        remaining_args = vector<string>(args.begin() + 2, args.end());
        return mode_t::config;
    }
    else
    {
        remaining_args = vector<string>(args.begin() + 1, args.end());
        return mode_t::normal;
    }
    return mode_t::error;
}

} // end namespace detail
} // end namespace okshell
