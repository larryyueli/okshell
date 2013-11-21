/*
 * normal_commander.h
 * The class that executes a normal command
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef NORMAL_COMMANDER_H_
#define NORMAL_COMMANDER_H_

#include <string>
#include <vector>
#include "local_matcher.h"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class NormalCommander
{
public:
    NormalCommander();
    
private:
    LocalMatcher local_matcher_;
    
public:
    // returns the return value of the execution of the command
    // input is the command vector without the leading "ok"
    // For example, {"recursively", "delete", "hpp", "files"}
    int process(const vector<string>& command) const;
};
    
} // end namespace detail
} // end namespace okshell

#endif /* NORMAL_COMMANDER_H_ */
