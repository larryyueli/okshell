/*
 * help_displayer.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "help_displayer.h"
#include <iostream>
#include "utils.h"

namespace okshell
{
namespace detail
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
    
} // end namespace detail
} // end namespace okshell
