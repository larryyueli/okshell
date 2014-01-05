/*
 * help_displayer.cc
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

#include "help_displayer.h"

#include <iostream>

#include "utils.h"

namespace okshell
{
using std::cout;
using std::endl;
using utils::boldface;

void HelpDisplayer::display() const
{
    cout << "\n\n================== " << boldface("HOW TO USE OkShell") << " ==================\n\n  "
         << "You could be in one of two modes when using OkShell: " << "\n  " 
         << boldface("NORMAL") << " mode or " << boldface("CONFIG") << " mode.\n\n  "
         << "When you are in " << boldface("NORMAL") << " mode, you just want to run some\n  " 
         << "command (90% of use cases). Just type `ok` followed\n  " 
         << "by whatever you want to do. For example, \n\n  "
         << "    " << boldface("$ ok replace \"good\" with \"great\" in txt files") << "\n\n  "
         << "When you are in " << boldface("CONFIG") << " mode occasionally, you want to \n  " 
         << "run some configuration tasks. Just type `ok` twice,\n  " 
         << "followed by some configuration command. For example, \n\n  "
         << "    " << boldface("$ ok ok cloud off") << "\n\n  "
         << "To see a list of the configuration commands, do\n\n  "
         << "    " << boldface("$ ok ok help") << "\n\n  " 
         << "To see this manual, do\n\n  "
         << "    " << boldface("$ ok help") << "\n\n" 
         << "======================= "<< boldface("THE END") << " ========================\n" 
         << endl;
}
    
} // end namespace okshell
