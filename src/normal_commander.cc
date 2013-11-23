/*
 * normal_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "normal_commander.h"
#include <iostream>
#include "local_matcher.h"
#include "cloud_matcher.h"
#include "globals.h"
#include "utils.h"
#include "keyboard_input.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;
using utils::vec_str;
using utils::exe_system;

NormalCommander::NormalCommander()
    : local_matcher_(kProfileLocal),
      cloud_matcher_(kProfileCloudDemo)
{}

int NormalCommander::process(const vector<string>& command) const
{
    cerr << "Matching local profile..." << endl;
    LocalMatchResult result;
    local_matcher_.match(command, result);
    if (result.flag == LocalMatchResultType::SURE)
    {
        cerr << "Found match in local profile." << endl;
        cerr << "MATCHED: " 
             << result.match_results[0].color_str_human() 
             << endl;
        cerr << "REAL: " 
             << result.match_results[0].color_str_real() 
             << endl;
        cerr << "Running...\n" << endl;
        string real_command 
            = result.match_results[0].plain_str_real();
        int rv = exe_system(real_command);
        return rv;
    }
    else if (result.flag == LocalMatchResultType::UNSURE)
    {
        cerr << "Possible matches in local profile." << endl;
        cerr << result.repr_multiple() << endl;
        IntegerChoiceInputValidator validator(result.match_results.size());
        size_t choice = keyboard_input<size_t>(
                "Choose one number, 0 for none: [1]", true, 1, &validator);
        if (choice == 0)
        {
            cerr << "You chose none of the result." << endl;
            YesNoInputValidator yn_validator;
            string use_cloud = keyboard_input<string>(
                    "Learn from cloud? [Y/n] ", true, "y", &yn_validator);
            
            // use_cloud must be "y" or "n"
            if (use_cloud == "y")
            {
                cerr << "Learning from the cloud..." << endl;
                CloudMatchResult cloud_result;
                cloud_matcher_.match(command, cloud_result);
                if (cloud_result.flag == LocalMatchResultType::SURE)
                {
                    // this case never happens
                }
                else if (cloud_result.flag == LocalMatchResultType::UNSURE)
                {
                    cerr << "Matches from the cloud." << endl;
                    cerr << cloud_result.repr_multiple() << endl;
                }
                else if (cloud_result.flag == LocalMatchResultType::NONE)
                {
                    
                }
                else // "ERROR"
                {
                    
                }
            }
            else // "n"
            {
                
            }
        }
        else // choice is one of candidates
        {
            
        }
        
    }
    else if (result.flag == LocalMatchResultType::NONE)
    {
        
    }
    else // ERROR
    {
        
    }
    return 0;
}

} // end namespace detail
} // end namespace okshell

