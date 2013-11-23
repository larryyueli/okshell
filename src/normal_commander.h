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
#include "cloud_matcher.h"

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
    CloudMatcher cloud_matcher_; // TODO: changed use CloudMatcher class
    
public:
    // returns the return value of the execution of the command
    // input is the command vector without the leading "ok"
    // For example, {"recursively", "delete", "hpp", "files"}
    // The command is preprocesses with quoted entries combined
    int process(const vector<string>& command) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(NormalCommander);
};
    
} // end namespace detail
} // end namespace okshell

#endif /* NORMAL_COMMANDER_H_ */
