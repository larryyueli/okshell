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

mode_t ModeParser::parse(const vector<string>& args) const
{
    if (args.empty())
        throw std::runtime_error("ModeParser::parse, args is empty");
    else if (args.size() == 1)
        return mode_t::empty;
    else if (lowercase(args[1]) == "ok")
        return mode_t::special;
    else
        return mode_t::normal;
}

} // end namespace detail
} // end namespace okshell
