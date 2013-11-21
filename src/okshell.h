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
#include <iostream>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;
using std::cout;
using std::endl;

class OkShell
{
public:
    OkShell() : ph_(0) {}
    ~OkShell() {}
    
private:
    int ph_;
    
public:
    // input: args is the vector of arguments passed from command
    // output: return value is the exit code, 0 normal, 1 abnormal
    int run(const vector<string>& args);
};

} // end namespace detail
using detail::OkShell;
} // end namespace okshell

#endif /* OKSHELL_H_ */
