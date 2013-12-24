/*
 * config_help_displayer.cc
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

#include "config_help_displayer.h"
#include <iostream>
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::cout;
using std::cerr;
using std::endl;
using utils::boldface;

void ConfigHelpDisplayer::display() const
{
    cout << "\n========================= " << boldface("OkShell Config Guide") << " =========================\n\n  ";
    cout << "To perform a configuration task, type `ok ok` followed by one of the\n  ";
    cout << "following options. For example,\n\n  ";
    cout << "    " << boldface("$ ok ok interactive off") << "\n\n  ";
    cout << "OPTIONS:\n\n  ";
    cout << "    " << boldface("interactive on/off") << "\n  ";
    cout << "        When turned off, messages starting with [OKSHELL] do not show\n  ";
    cout << "        up. The command is executed only when having a confident match.\n\n  ";
    cout << "    " << boldface("cloud on/off") << "\n  ";
    cout << "        Turn on/off connection to cloud.\n\n  ";
    cout << "    " << boldface("sync") << "\n  ";
    cout << "        Synchronize local pofile with cloud.\n\n  ";
    cout << "    " << boldface("restore") << "\n  ";
    cout << "        Restore local profile from cloud with user ID.\n\n  ";
    cout << "    " << boldface("userid") << "\n  ";
    cout << "        Display the OkShell user ID.\n\n  ";
    cout << "    " << boldface("remove") << "\n  ";
    cout << "        Remove a command from profile.\n\n  ";
//    cout << "    " << boldface("display profile/config") << "\n  ";
//    cout << "        Print out profile/config in readable format.\n\n  ";
//    cout << "    " << boldface("reinstall") << "\n  ";
//    cout << "        Start like a new OkShell user, with empty profile and newly\n  ";
//    cout << "        assigned user ID.\n\n";
    cout << "=============================== " << boldface("THE END") << " ================================\n  ";
    cout << endl;
}

    
} // end namespace detail
} // end namespace okshell

