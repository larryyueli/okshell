/*
 * normal_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "normal_commander.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "local_matcher.h"
#include "cloud_matcher.h"
#include "globals.h"
#include "utils.h"
#include "keyboard_input.h"
#include "profile_writer.h"
#include "user_config.h"
#include "cloud_sync.h"
#include "logger.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;
using utils::vec_str;
using utils::exe_system;
using utils::boldface;
using std::setw;

NormalCommander::NormalCommander()
    : local_matcher_(kProfileLocal),
      cloud_matcher_(kProfileCloudDemo)
{}

int NormalCommander::process(const vector<string>& command) const
{
    cerr << endl;
    mycerr << "Matching local profile..." << endl;
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SURE)
    {
        return process_local_sure(result);
    }
    else if (result.flag == LocalMatchResultType::UNSURE)
    {
        return process_local_unsure(command, result);
    }
    else if (result.flag == LocalMatchResultType::NONE)
    {
        return process_local_none(command);
    }
    else // ERROR
    {
        throw std::runtime_error(
                "NormalCommander::process, local match got ERROR result");
    }
    throw std::logic_error("NormalCommander::process, reached the end");
    return 1;
}

int NormalCommander::process_local_sure(const LocalMatchResult& result) const
{
    mycerr << "Found match in local profile." << endl;
    mycerr << "\n";
    mycerr << os_label(kOSHuman)
           << result.match_results[0].color_str_human() << endl;
    mycerr << os_label(kOSLinux) 
           << result.match_results[0].color_str_real() << endl;
    string real_command 
        = result.match_results[0].plain_str_real();
    mycerr << "\n";
    mycerr << kPrintOutExecuting << endl;
    int rv = exe_system(real_command);
    return rv;
}

int NormalCommander::process_local_unsure(const vector<string>& command, 
        const LocalMatchResult& result) const
{
    mycerr << "Possible matches in local profile." << endl;
    result.display_multiple();
    IntegerChoiceInputValidator validator(result.match_results.size());
    size_t choice = keyboard_input<size_t>(
            "Choose one number, 0 for none [1]:", true, 1, &validator);
    if (choice == 0)
    {
        mycerr << "You chose none of the result." << endl;
        YesNoInputValidator yn_validator;
        string use_cloud = keyboard_input<string>(
                "Learn from cloud? [Y/n]", true, "y", &yn_validator);
        
        // use_cloud must be "y" or "n"
        if (use_cloud == "y")
        {
            bool success = false;
            int rv = process_cloud(command, success);
            if (success)
            {
                return rv;
            }
            else
            {
                string add_manually = keyboard_input<string>(
                        kPromptAddManually, true, "y", &yn_validator);
                if (add_manually == "y")
                {
                    rv = process_manual_add(command);
                    return rv;
                }
                else
                {
                    // no more option available, give up.
                    return 2;
                }
            }
        }
        else // "n"
        {
            string add_manually = keyboard_input<string>(
                    kPromptAddManually, true, "y", &yn_validator);
            if (add_manually == "y")
            {
                return process_manual_add(command);
            }
            else
            {
                // no more option available, give up.
                return 2;
            }
        }
    }
    else // choice is one of candidates
    {
        mycerr << "Command " << choice << " chosen." << endl;
        string real_command 
            = result.match_results[choice - 1].plain_str_real();
        mycerr << kPrintOutExecuting << endl;
        int rv = exe_system(real_command);
        return rv;
    }
    throw std::logic_error(
            "NormalCommander::process_local_unsure, reached the end");
    return 1;
}

int NormalCommander::process_local_none(const vector<string>& command) const
{
    mycerr << "Did not find good match in local profile." << endl;
    YesNoInputValidator yn_validator;
    string use_cloud = keyboard_input<string>(
            "Learn from cloud? [Y/n]", true, "y", &yn_validator);
    
    // use_cloud must be "y" or "n"
    if (use_cloud == "y")
    {
        bool success = false;
        int rv = process_cloud(command, success);
        if (success)
        {
            return rv;
        }
        else
        {
            string add_manually = keyboard_input<string>(
                    kPromptAddManually, true, "y", &yn_validator);
            if (add_manually == "y")
            {
                rv = process_manual_add(command);
                return rv;
            }
            else
            {
                // no more option available, give up.
                return 2;
            }
        }
    }
    else // "n"
    {
        string add_manually = keyboard_input<string>(
                kPromptAddManually, true, "y", &yn_validator);
        if (add_manually == "y")
        {
            return process_manual_add(command);
        }
        else
        {
            // no more option available, give up.
            return 2;
        }
    }
    throw std::logic_error(
            "NormalCommander::process_local_none, reached the end");
    return 1;
}

int NormalCommander::process_cloud(const vector<string>& command, 
        bool& success) const
{
    mycerr << "Learning from the cloud..." << endl;
    usleep(1000000); // TEMP, simulate the delay to communicate with cloud
    CloudMatchResult result;
    cloud_matcher_.match(command, result);
    if (result.flag == CloudMatchResultType::SURE)
    {
        // this case never happens because we always ask the user
        // for confirmation when learning from cloud.
        throw std::runtime_error(
                "NormalCommander::process_cloud: got SURE result.");
    }
    else if (result.flag == CloudMatchResultType::UNSURE)
    {
        mycerr << "Matches from the cloud." << endl;
        mycerr << result.repr_multiple() << endl;
        IntegerChoiceInputValidator validator(
                result.match_results.size());
        size_t cloud_choice = keyboard_input<size_t>(
                "Choose the one you want to learn, 0 for none: [1]", 
                true, 1, &validator);
        
        if (cloud_choice == 0)
        {
            success = false;
            return 2;
        }
        else
        {
            mycerr << "Command " << cloud_choice << "selected" << endl;
            mycerr << "Please write below your own human version \
                    of this command." << endl;
            CommandInputValidator cmd_validator;
            string human_command = keyboard_input<string>(
                    "$ ok", false, "", &cmd_validator);
            string real_command 
            = result.match_results[cloud_choice - 1].plain_str_real_profile();
            
            add_to_local_and_cloud(human_command, real_command);
            
            YesNoInputValidator yn_validator;
            string run_it = keyboard_input<string>("Run it now? [Y/N]", 
                    true, "y", &yn_validator);
            if (run_it == "y")
            {
                string real_command 
                    = result.match_results[0].plain_str_real_command();
                mycerr << kPrintOutExecuting << endl;
                int rv = exe_system(real_command);
                success = true;
                return rv;
            }
            else
            {
                return 2;
            }
        }
        throw std::logic_error(
                "NormalCommander::process_cloud: reached the end");
        return 1;
    }
    else if (result.flag == CloudMatchResultType::NONE)
    {
        mycerr << "Did not find good match in the cloud" << endl;
        success = false;
        return 2;
    }
    else // "ERROR"
    {
        throw std::runtime_error(
                "NormalCommander::process, local match got ERROR result");
    }
    throw std::logic_error("NormalCommander::process_cloud, reached the end");
    return 1;
}

int NormalCommander::process_manual_add(const vector<string>& command) const
{
    CommandInputValidator validator;
    string human_command = keyboard_input<string>(
            "Write the human command: $ ok", false, "", &validator);
    string real_command = keyboard_input<string>(
            "Write the real command: $", false, "", &validator);
    add_to_local_and_cloud(human_command, real_command);
    return 2;
}

void NormalCommander::add_to_local_and_cloud(
        const string& human_command, const string& real_command) const
{
    ProfileWriter profile_writer{};
    bool add_success = profile_writer.add_command_to_profile(
            human_command, real_command);
    if (add_success)
    {
        mycerr << "Command added to local profile." << endl;
        UserConfig user_config{};
        if (user_config.cloud_enabled())
        {
            mycerr << "Syncing with cloud profile..." << endl;
            CloudSync cloud{};
            bool sync_success = cloud.sync();
            if (!sync_success)
            {
                mycerr << "Syncing failed, \
                         please try again later using `ok ok sync`" << endl;
            }
            else
            {
                mycerr << "Syncing done." << endl;
            }
        }
    }
    else
    {
        mycerr << "Did not add new command, please try again." << endl;
    }
    return;
}

} // end namespace detail
} // end namespace okshell

