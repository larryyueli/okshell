/*
 * mode_parser.hpp
 * Parser used to determine whether it is normal or special mode
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef MODE_PARSER_HPP_
#define MODE_PARSER_HPP_

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
    MainMode parse(const vector<string>& args, 
            vector<string>& remaining_args) const; 
};
} // end namespace detail
} // end namespace okshell


#endif /* MODE_PARSER_HPP_ */
