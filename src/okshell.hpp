/*
 * okshell.hpp
 * The main class of OkShell
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#ifndef OKSHELL_HPP_
#define OKSHELL_HPP_

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
    OkShell() : ph_(0)
    {
        cout << "OkShell constructor." << endl;
    }
    ~OkShell() {}
    
private:
    int ph_;
    
public:
    int run(const vector<string>& args);
};

} // end namespace detail
using detail::OkShell;
} // end namespace okshell

#endif /* OKSHELL_HPP_ */
