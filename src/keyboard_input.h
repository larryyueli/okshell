/*
 * keyboard_input.h
 * classes used to collect and validate keyboard input
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

#ifndef KEYBOARD_INPUT_H_
#define KEYBOARD_INPUT_H_

#include <string>

#include "common_defs.h"

namespace okshell
{

// Based class of input validators.
template <typename T>
class InputValidatorBase
{
public:
    InputValidatorBase() {}
    virtual ~InputValidatorBase () {}
    
public:
    // return value: whether validation succeeded.
    // result: the casted result to pass to keyboard_input
    // error_message: error message when validation fails, 
    // error_message is empty string if success.
    virtual bool validate(const std::string& input, T& result, 
            std::string& error_message) = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(InputValidatorBase);
};

// The function called to get a valid keyboard input
// Return default value when input is empty
// On invalid input, retry untils the input is valid
template <typename T>
T keyboard_input(const std::string& prompt_message, bool with_default, 
        const T& default_value, InputValidatorBase<T>* validator);

// Input validator that checks the input of choices from 
// an integer labelled menu
class IntegerChoiceInputValidator : public InputValidatorBase<size_t>
{
public:
    // n_choices is the total number of choices
    IntegerChoiceInputValidator(size_t n_choices);

private:
    size_t n_choices_; // number of choices
    
public:
    bool validate(const std::string& input, size_t& result, 
            std::string& error_message);  
};

// Input validator the checks the answer of a yes or no questions.
// Valid input: y, n, yes, no
// Possible result: "y" or "n"
class YesNoInputValidator : public InputValidatorBase<std::string>
{
public:
    YesNoInputValidator() {}
    
public:
    bool validate(const std::string& input, std::string& result, 
            std::string& error_message);  
};

// Input validator that checks the input when manually adding commands
// check if the string has unclosed argument brackets <arg1>
class CommandInputValidator : public InputValidatorBase<std::string>
{
public:
    CommandInputValidator() {}
    
public:
    bool validate(const std::string& input, std::string& result, 
            std::string& error_message);
};

// wrappers that include the keyboard_input call with validator
// Interger choice wrapper, always has default value
size_t integer_choice_input(const std::string& prompt_message, 
        const size_t& default_value, size_t n_choices);

// Yes/No wrapper, always has default value
std::string yes_no_input(const std::string& prompt_message, 
        const std::string& default_value);

// CommandInput always no default value
std::string command_input(const std::string& prompt_message);

} // end namespace okshell

#endif /* KEYBOARD_INPUT_H_ */
