/*
 * keyboard_input.cc
 *
 * Copyright (C) 2013  Larry Yueli Zhang
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "keyboard_input.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "utils.h"
#include "logger.h"

namespace okshell
{
using std::cin;
using std::cerr;
using std::getline;
using boost::lexical_cast;
using utils::lowercase;

// TODO, allow arrow keys in cin mode
template <typename T>
T keyboard_input(const string& prompt_message, bool with_default, 
        const T& default_value, InputValidatorBase<T>* validator)
{
    mycerr << prompt_message << " ";
    bool done = false;
    T result{};
    while (!done)
    {
        string input;
        getline(cin, input);
        boost::trim(input); // remove leading and tailing spaces
        if (input.empty())
        {
            if (with_default)
            {
                return default_value;
            }
            else
            {
                mycerr << "Input was empty. Try again.\n";
                mycerr << prompt_message << " ";
            }
        }
        else
        {
            string error_message;
            bool is_valid = validator->validate(input, result, error_message);
            if (is_valid)
                done = true;
            else
            {
                mycerr << error_message << "\n"; 
                mycerr << prompt_message << " ";
            }
        }
    }
    return result;
}

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
        error_message = "Please enter Y or N.";
        return false;
    }
    throw std::logic_error("YesNoInputValidator::validate: Line 115");
    return false;
}

bool CommandInputValidator::validate(const string& input, string& result, 
        string& error_message)
{
    // TODO add checking for unclosed brackets
    if (input.empty())
    {
        error_message = "Command cannot be empty.";
        return false;
    }
    result = input;
    return true;
}

size_t integer_choice_input(const string& prompt_message, 
        const size_t& default_value, size_t n_choices)
{
    IntegerChoiceInputValidator validator{n_choices};
    return keyboard_input<size_t>(prompt_message, true, 
            default_value, &validator);
}

string yes_no_input(const string& prompt_message, const string& default_value)
{
    YesNoInputValidator validator;
    return keyboard_input<string>(prompt_message, true, 
            default_value, &validator);
}

string command_input(const string& prompt_message)
{
    CommandInputValidator validator;
    return keyboard_input<string>(prompt_message, false, "", &validator);
}

} // end namespace okshell

