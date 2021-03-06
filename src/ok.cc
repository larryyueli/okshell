/*
 * ok.cc
 * The main file for the ok executable.
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

#include <string>
#include <vector>

#include "okshell.h"
#include "initializer.h"

using std::string;
using std::vector;

int main(int argc, char **argv)
{
    okshell::Initializer initer{};
    if (initer.uninitialized())
    {
        initer.init();
        initer.welcome();
        return 0;
    }
    vector<string> args;
    for (int i = 0; i < argc; ++i)
        args.push_back(argv[i]);
    okshell::OkShell oks{};
    int ret = oks.run(args);
    return ret;
}
