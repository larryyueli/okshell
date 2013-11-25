/*
 * okinit.cc
 * A test program used to create the initial setting for okshell
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#include "globals.h"
#include "command_profile.h"

namespace okshell
{
namespace detail
{
void init()
{
    CommandProfile profile;
    profile.write_to_file(kProfileLocal);
    profile.write_to_file(kProfileCloudDemo);
}
} // end namespace detail
using detail::init;
} // end namespace okshell

int main()
{
    okshell::init();
}
