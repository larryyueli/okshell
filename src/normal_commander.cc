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

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;
using utils::vec_str;

NormalCommander::NormalCommander()
    : local_matcher_(kProfileLocal)
{}

int NormalCommander::process(const vector<string>& command) const
{
    cerr << "Matching local profile..." << endl;
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SINGLE)
    {
        cerr << "Found match in local profile." << endl;
        cerr << "Matched command: " 
             << vec_str(vec_color(result.match_results[0].human_command)) 
             << endl;
        cerr << "Real command: " 
             << vec_str(vec_color(result.match_results[0].real_command)) 
             << endl;
        cerr << "Running...\n" << endl;
        string real_command 
            = vec_str(vec_plain(result.match_results[0].real_command));
        int rv = utils::exe_system(real_command);
        return rv;
    }
    else if (result.flag == LocalMatchResultType::MULTIPLE)
    {
        //TODO
    }
    return 0;
}

} // end namespace detail
} // end namespace okshell

