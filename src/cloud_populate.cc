/*
 * cloud_populate.cc
 * A small program to populate the cloud profile for demo
 *
 *  Created on: 2013-11-27
 *      Author: Larry Yueli Zhang
 */

#include <iostream>
#include "common_defs.h"
#include "keyboard_input.h"
#include "profile_writer.h"
#include "globals.h"
#include "logger.h"

namespace okshell
{
namespace detail
{
using std::endl;

void run()
{
    CommandInputValidator validator;
    string human_command = keyboard_input<string>(
            "Write the human command: $ ok", false, "", &validator);
    string real_command = keyboard_input<string>(
            "Write the real command: $", false, "", &validator);
    ProfileWriter profile_writer{kProfileCloudDemo};
    bool add_success = profile_writer.add_command_to_profile(
            human_command, real_command);
    mycerr << (add_success ? "Success." : "Failed") << endl;
    return;
}
} // end namespace detail
using detail::run;
} // end namespace okshell

int main()
{
    okshell::run();
    return 0;
}
