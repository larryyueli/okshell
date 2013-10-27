/*
 * okshell.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#include "okshell.hpp"
#include "mode_parser.hpp"

namespace okshell
{
namespace detail
{

int OkShell::run(const vector<string>& args) // args could be empty vector
{
    ModeParser mparser{};
    mode_t mode = mparser.parse(args);
    if (mode == mode_t::empty)
    {
        std::cout << "help empty" << endl;
    }
    else if (mode == mode_t::normal)
    {
        std::cout << "help normal" << endl;
    }
    else
    {
        std::cout << "help special" << endl;
    }
    return 0;
}
} // end namespace detail
} // end namespace okshell
