/*
 * okshell.h
 * The main class of OkShell
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#ifndef OKSHELL_H_
#define OKSHELL_H_

#include <string>
#include <vector>
#include "common_defs.h"
#include "config.h"
#include "globals.h"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class OkShell
{
public:
    OkShell() : config_(kConfigFile) {}
    
private:
    Config      config_;
    
public:
    // input: args is the vector of arguments passed from command
    // output: return value is the exit code, 0 normal, 1 abnormal
    int run(const vector<string>& args);
    
private:
    // display welcome message and ask initial questions
    // only used in demo.
    void welcome() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(OkShell);
};

} // end namespace detail
using detail::OkShell;
} // end namespace okshell

#endif /* OKSHELL_H_ */
