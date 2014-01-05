/*
 * okshell.cpp
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

#include "okshell.h"

#include <iostream>

#include "mode_parser.h"
#include "help_displayer.h"
#include "normal_commander.h"
#include "config_commander.h"
#include "logger.h"
#include "keyboard_input.h"
#include "utils.h"
#include "logger.h"

namespace okshell
{
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using utils::boldface;

// For the meaning of return values from process functions,
// see the comment for NormalCommander::process in normal_commander.h
int OkShell::run(const vector<string>& args) // args could be empty vector
{
    int rv = 0;
    vector<string> remaining_args{};
    ModeParser mode_parser{};
    MainMode mode = mode_parser.parse(args, remaining_args);
    if (mode == MainMode::HELP || mode == MainMode::EMPTY)
    {
        HelpDisplayer help_displayer{};
        help_displayer.display();
    }
    else if (mode == MainMode::NORMAL)
    {
        NormalCommander commander{config_};
        rv = commander.process(remaining_args);
        if (rv == 2)
        {
            mycerr << "\n";
            mycerr << "Did not execute a command." << endl;
            rv = 0;
        }
        else if (rv == 3)
        {
            mycerr << "\n";
            mycerr << "Learned something new, try running the command again."
                   << endl;
            rv = 0;
        }
        if (config_.interactive_on())
        {
            cerr << endl;
        }
    }
    else if (mode == MainMode::CONFIG)
    {
        ConfigCommander commander{config_};
        commander.process(remaining_args);
        cerr << endl;
    }
    else
    {
        throw OkShellException("OkShell::run, invalide mode_t");
    }
    return rv;
}

} // end namespace okshell

