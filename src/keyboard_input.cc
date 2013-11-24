/*
 * keyboard_input.cc
 *
 *  Created on: 2013-11-21
 *      Author: Larry Yueli Zhang
 */

#include "keyboard_input.h"
#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::cin;
using std::cerr;
using std::getline;
using boost::lexical_cast;
using utils::lowercase;

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
        boost::trim(input); // remove leading tailing spaces
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

// instantiations
template size_t keyboard_input(const string& prompt_message, bool with_default,
        const size_t& default_value, InputValidatorBase<size_t>* validator);

template string keyboard_input(const string& prompt_message, bool with_default,
        const string& default_value, InputValidatorBase<string>* validator);


IntegerChoiceInputValidator::IntegerChoiceInputValidator(size_t n_choices)
    : n_choices_(n_choices)
{}

bool IntegerChoiceInputValidator::validate(
        const string& input, size_t& result, string& error_message)
{
    try
    {
        result = lexical_cast<size_t>(input);
    }
    catch (const boost::bad_lexical_cast& e)
    {
        error_message = "The input is not a number.";
        return false;
    }
    if (result > n_choices_)
    {
        error_message = "Chosen number does not exist.";
        return false;
    }
    else
    {
        error_message = "";
        return true;
    }
    throw std::logic_error("IntegerChoiceInputValidator::validate: Line 91");
    return false;
}

bool YesNoInputValidator::validate(const string& input, string& result, 
        string& error_message)
{
    string low = lowercase(input);
    if (low == "y" || low == "yes")
    {
        result = "y";
        error_message = "";
        return true;
    }
    else if (low == "n" || low == "no")
    {
        result = "n";
        error_message = "";
        return true;
    }
    else
    {
        error_message = "Please enter y or n.";
        return false;
    }
    throw std::logic_error("YesNoInputValidator::validate: Line 115");
    return false;
}

bool CommandInputValidator::validate(const string& input, string& result, 
        string& error_message)
{
    // TODO add checking for unclosed brackets
    return true;
}


} // end namespace detail
} // end namespace okshell
