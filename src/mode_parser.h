/*
 * mode_parser.h
 * Parser used to determine whether it is normal or special mode
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef MODE_PARSER_H_
#define MODE_PARSER_H_

#include <string>
#include <vector>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

enum class MainMode
{
    ERROR=0, EMPTY, NORMAL, CONFIG
};
    
class ModeParser
{
public:
    ModeParser() {}
    
public:
    // return the working mode for the command, i.e., NORMAL or CONFIG
    // or just display help
    // Also, perform preprocessing such as combining quoted entries, 
    // and put clean result in remaining_args
    MainMode parse(const vector<string>& args, 
            vector<string>& remaining_args) const; 
};
} // end namespace detail
} // end namespace okshell


#endif /* MODE_PARSER_H_ */
