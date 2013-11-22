/*
 * normal_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "normal_commander.h"
#include <iostream>
#include "local_matcher.h"
#include "globals.h"
#include "utils.h"
#include "keyboard_input.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;
using utils::vec_str;
using utils::exe_system;

NormalCommander::NormalCommander()
    : local_matcher_(kProfileLocal)
{}

int NormalCommander::process(const vector<string>& command) const
{
    cerr << "Matching local profile..." << endl;
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SURE)
    {
        cerr << "Found match in local profile." << endl;
        cerr << "MATCHED: " 
             << result.match_results[0].color_str_human() 
             << endl;
        cerr << "REAL: " 
             << result.match_results[0].color_str_real() 
             << endl;
        cerr << "Running...\n" << endl;
        string real_command 
            = result.match_results[0].plain_str_real();
        int rv = exe_system(real_command);
        return rv;
    }
    else if (result.flag == LocalMatchResultType::UNSURE)
    {
        cerr << "Possible matches in local profile." << endl;
        cerr << result.repr_multiple() << endl;
        IntegerChoiceInputValidator validator(result.match_results.size());
        int choice = keyboard_input<size_t>("Choose command: [1]", true,
                1, &validator);
        choice = choice; // TODO
    }
    else if (result.flag == LocalMatchResultType::NONE)
    {
        
    }
    else // ERROR
    {
        
    }
    return 0;
}

} // end namespace detail
} // end namespace okshell

