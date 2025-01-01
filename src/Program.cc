/*
 * Program.cc - Copyright (c) 2024-2025 - Olivier Poncet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "Console.h"
#include "Brainfuck.h"
#include "Program.h"

// ---------------------------------------------------------------------------
// Program
// ---------------------------------------------------------------------------

int Program::main(const std::vector<std::string>& args)
{
    std::vector<std::string> expressions;

    auto progname = [&]() -> const char*
    {
        const char* path = args[0].c_str();
        const char* sep  = ::strrchr(path, '/');

        if(sep != nullptr) {
            return sep + 1;
        }
        return path;
    };

    auto usage = [&]() -> void
    {
        Console::println("Usage: %s [EXPRESSIONS...]", progname());
        Console::println("");
    };

    auto parse = [&]() -> bool
    {
        int argi = -1;
        for(auto& arg : args) {
            if(++argi == 0) {
                continue;
            }
            else if(arg == "--help") {
                usage();
                return false;
            }
            else {
                expressions.push_back(arg);
            }
        }
        return true;
    };

    auto execute = [&]() -> void
    {
        const std::unique_ptr<bf::Interpreter> brainfuck(new bf::Interpreter());

        for(auto& expression : expressions) {
            brainfuck->eval(expression);
        }
    };

    auto run = [&]() -> int
    {
        try {
            if(parse()) {
                execute();
            }
        }
        catch(const std::exception& e) {
            Console::errorln("error: %s", e.what());
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    };

    return run();
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    const std::vector<std::string> args(argv, argv + argc);

    return Program::main(args);
}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
