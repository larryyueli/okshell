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

int NormalCommander::process(const vector<string>& command) const
{   
    if (config_.interactive_on())
    {
        return process_interactive_on(command);
    }
    else
    {
        return process_interactive_off(command);
    }
}

int NormalCommander::process_interactive_on(
        const vector<string>& command) const
{
    cerr << "\n";
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

int NormalCommander::process_interactive_off(
        const vector<string>& command) const
{
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SURE)
    {
        return process_local_sure(result, false);
    }
    else
    {
        cerr << "No command executed by OkShell" << endl;
    }
    return 1;
}

int NormalCommander::process_local_sure(const LocalMatchResult& result, 
        bool interactive) const
{

    if (interactive)
    {
        mycerr << "Found match in local profile." << endl;
        mycerr << "\n";
        mycerr << "  " << os_label(kOSHuman) << kEXE << " "
               << result.match_results[0].color_str_human() << endl;
        mycerr << "  " << os_label(kOSLinux)
               << result.match_results[0].color_str_real() << endl;
        mycerr << "\n";
        mycerr << kPrintOutExecuting << endl;
    }
    string real_command 
        = result.match_results[0].plain_str_real();
    int rv = exe_system(real_command);
    return rv;
}

int NormalCommander::process_local_unsure(const vector<string>& command, 
        const LocalMatchResult& result) const
{
    mycerr << "Possible matches in local profile:" << endl;
    result.display_multiple();
    size_t choice = integer_choice_input("Choose one number, 0 for none: [1]",
            1, result.match_results.size());
    if (choice == 0)
    {
        mycerr << "Nothing chosen." << endl;
        mycerr << "\n";
        string use_cloud = yes_no_input(kPromptLearnCloud, "y");
        
        // use_cloud must be "y" or "n"
        if (use_cloud == "y")
        {
            int rv = process_cloud(command);
            if (rv == 3) // Learned a new command
            {
                return rv;
            }
            else if (rv == 2)// Did not learn anything from cloud
            {
                mycerr << "\n";
                string add_manually = yes_no_input(kPromptAddManually, "y");
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
            else
            {
                throw std::runtime_error(
                "process_local_unsure, invalid return value of process_cloud()");
            }
        }
        else // "n"
        {
            mycerr << "\n";
            string add_manually = yes_no_input(kPromptAddManually, "y");
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
    mycerr << "No good match in local profile." << endl;
    mycerr << "\n";
    string use_cloud = yes_no_input(kPromptLearnCloud, "y");
    
    // use_cloud must be "y" or "n"
    if (use_cloud == "y")
    {
        int rv = process_cloud(command);
        if (rv == 3) // Learned a new command from cloud
        {
            return rv;
        }
        else if (rv == 2) // Did not learn anything from cloud
        {
            mycerr << "\n";
            string add_manually = yes_no_input(kPromptAddManually, "y");
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
        else
        {
            throw std::runtime_error(
              "process_local_none, invalid return value of process_cloud()");
        }
    }
    else // "n"
    {
        mycerr << "\n";
        string add_manually = yes_no_input(kPromptAddManually, "y");
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

int NormalCommander::process_cloud(const vector<string>& command) const
{
    mycerr << "Learning from the cloud..." << endl;
    usleep(1000000); // TEMP, simulate the delay to communicate with cloud
    CloudMatchResult result{};
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
        result.display_multiple();
        size_t cloud_choice = integer_choice_input(
                "Choose the one you want to learn, 0 for none: [1]",
                1, result.match_results.size());
        
        if (cloud_choice == 0)
        {
            return 2;
        }
        else
        {
            mycerr << "Command " << cloud_choice << " selected" << endl;
            mycerr << "\n";
            mycerr << "Write your own " << boldface("HUMAN") 
                   << " template of this command." << endl;
            string human_command = command_input("$ ok");
            mycerr << "\n";
            string real_command 
            = result.match_results[cloud_choice - 1].plain_str_real_profile();
            add_to_local_and_cloud(human_command, real_command);
            return 3;
        }
        throw std::logic_error(
                "NormalCommander::process_cloud: reached the end");
        return 1;
    }
    else if (result.flag == CloudMatchResultType::NONE)
    {
        mycerr << "No good match in the cloud" << endl;
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
    mycerr << "\n";
    mycerr 
    << "Write the " << boldface("HUMAN") << " command template." << endl;
    mycerr << "EXAMPLE: $ ok recursively delete " << boldface("<arg1>") 
           << " files" << endl;
    string human_command = command_input("$ ok");
    mycerr << "\n";
    mycerr << "Write the " << boldface("REAL") << " command template." << endl;
    mycerr << "EXAMPLE: $ find . -name \"*." 
           << boldface("<arg1>") << "\" | xargs rm -rf" << endl;
    string real_command = command_input("$");
    mycerr << "\n";
    add_to_local_and_cloud(human_command, real_command);
    return 3;
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

