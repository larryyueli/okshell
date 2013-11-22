/*
 * keyboard_input.cc
 *
 *  Created on: 2013-11-21
 *      Author: Larry Yueli Zhang
 */

#include "keyboard_input.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace okshell
{
namespace detail
{
using std::cin;
using std::cerr;
using std::getline;
using boost::algorithm::trim;

template <typename T>
T keyboard_input(const string& prompt_message, bool with_default, 
        const T& default_value, InputValidatorBase<T>* validator)
{
    cerr << prompt_message << " ";
    bool done = false;
    T result{};
    while (!done)
    {
        string input;
        getline(cin, input);
        trim(input); // remove leading tailing spaces
        if (input.empty())
        {
            if (with_default)
            {
                return default_value;
            }
            else
            {
                cerr << "Input was empty. Try again.\n"
                     << prompt_message << " ";
            }
        }
        else
        {
            string error_message;
            bool is_valid = validator->validate(input, result, error_message);
            if (is_valid)
                done = true;
            else
                cerr << error_message << "\n" 
                     << prompt_message << " "; 
        }
    }
    return result;
}

template size_t keyboard_input(const string& prompt_message, bool with_default,
        const size_t& default_value, InputValidatorBase<size_t>* validator);

IntegerChoiceInputValidator::IntegerChoiceInputValidator(size_t n_choices)
    : n_choices_(n_choices)
{}

bool IntegerChoiceInputValidator::validate(
        const string& input, size_t& result, string& error_message)
{
    return true;
}

} // end namespace detail
} // end namespace okshell
