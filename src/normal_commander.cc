/*
 * normal_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "normal_commander.h"
#include <iostream>
#include "local_matcher.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;

int NormalCommander::process(const vector<string>& command) const
{
    cerr << "Matching local command profile..." << endl;
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SINGLE)
    {
        
    }
    return 0;
}

} // end namespace detail
} // end namespace okshell

