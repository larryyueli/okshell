/*
 * okshell.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#include "okshell.h"
#include <stdexcept>
#include <iostream>
#include "mode_parser.h"
#include "help_displayer.h"
#include "normal_commander.h"
#include "config_commander.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;

int OkShell::run(const vector<string>& args) // args could be empty vector
{
    vector<string> remaining_args{};
    ModeParser mode_parser{};
    MainMode mode = mode_parser.parse(args, remaining_args);
    if (mode == MainMode::EMPTY)
    {
        HelpDisplayer help_displayer{};
        help_displayer.display();
    }
    else if (mode == MainMode::NORMAL)
    {
        NormalCommander commander{};
        commander.process(remaining_args);
    }
    else if (mode == MainMode::CONFIG)
    {
        ConfigCommander commander{};
        commander.process(remaining_args);
    }
    else
    {
        throw std::runtime_error("OkShell::run, invalide mode_t");
    }
    cerr << endl;
    return 0;
}
} // end namespace detail
} // end namespace okshell
