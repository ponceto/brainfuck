/*
 * Brainfuck.cc - Copyright (c) 2024 - Olivier Poncet
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

// ---------------------------------------------------------------------------
// countof
// ---------------------------------------------------------------------------

#ifndef countof
#define countof(array) (sizeof(array) / sizeof(array[0]))
#endif

// ---------------------------------------------------------------------------
// bf::State
// ---------------------------------------------------------------------------

namespace bf {

State::State()
    : _value()
    , _count(countof(_value))
    , _index()
{
}

uint32_t State::next()
{
    return _index = ((_index + 1) % _count);
}

uint32_t State::prev()
{
    return _index = ((_index - 1) % _count);
}

uint8_t State::incr()
{
    if(_index >= _count) {
        throw std::out_of_range("index is out of range while incrementing value");
    }
    return ++_value[_index];
}

uint8_t State::decr()
{
    if(_index >= _count) {
        throw std::out_of_range("index is out of range while decrementing value");
    }
    return --_value[_index];
}

uint8_t State::peek()
{
    if(_index >= _count) {
        throw std::out_of_range("index is out of range while getting value");
    }
    return _value[_index];
}

uint8_t State::poke(const uint8_t value)
{
    if(_index >= _count) {
        throw std::out_of_range("index is out of range while setting value");
    }
    return _value[_index] = value;
}

}

// ---------------------------------------------------------------------------
// bf::Interpreter
// ---------------------------------------------------------------------------

namespace bf {

void Interpreter::eval(const std::string& expression)
{
    State       state;
    const char* begin = expression.c_str();
    const char* end   = begin + expression.length();

    if(parse(state, begin, end, 0, true) != end) {
        throw std::runtime_error("error while parsing");
    }
}

const char* Interpreter::parse(State& state, const char* begin, const char* end, const int level, const bool execute)
{
    auto unexpected_character = [&](const char character) -> void
    {
        const std::string what("unexpected character");

        throw std::runtime_error(what + ' ' + '<' + character + '>');
    };

    auto unbalanced_statement = [&]() -> void
    {
        const std::string what("unbalanced statement");

        throw std::runtime_error(what);
    };

    auto on_beg = [&](const char* iterator) -> const char*
    {
        const char* result = nullptr;

        if(execute != false) {
            while(state.peek() != 0) {
                result = parse(state, iterator + 1, end, level + 1, true);
            }
        }
        if(result == nullptr) {
            result = parse(state, iterator + 1, end, level + 1, false);
        }
        return result;
    };

    auto on_end = [&](const char* iterator) -> const char*
    {
        if(level <= 0) {
            unexpected_character(*iterator);
        }
        return iterator;
    };

    auto on_next = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            state.next();
        }
        return iterator;
    };

    auto on_prev = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            state.prev();
        }
        return iterator;
    };

    auto on_incr = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            state.incr();
        }
        return iterator;
    };

    auto on_decr = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            state.decr();
        }
        return iterator;
    };

    auto on_peek = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            Console::putchar(state.peek());
        }
        return iterator;
    };

    auto on_poke = [&](const char* iterator) -> const char*
    {
        if(execute != false) {
            state.poke(Console::getchar());
        }
        return iterator;
    };

    auto do_parse = [&]() -> const char*
    {
        bool comment = false;
        for(auto iterator = begin; iterator != end; ++iterator) {
            const auto character = *iterator;
            if(comment != false) {
                if(character == TOK_LF) {
                    comment = false;
                }
            }
            else switch(character) {
                case TOK_CR:
                case TOK_LF:
                case TOK_TAB:
                case TOK_SPACE:
                    break;
                case TOK_COMMENT:
                    comment = true;
                    break;
                case TOK_BEG:
                    iterator = on_beg(iterator);
                    break;
                case TOK_END:
                    iterator = on_end(iterator);
                    return iterator;
                case TOK_NEXT:
                    iterator = on_next(iterator);
                    break;
                case TOK_PREV:
                    iterator = on_prev(iterator);
                    break;
                case TOK_INCR:
                    iterator = on_incr(iterator);
                    break;
                case TOK_DECR:
                    iterator = on_decr(iterator);
                    break;
                case TOK_PEEK:
                    iterator = on_peek(iterator);
                    break;
                case TOK_POKE:
                    iterator = on_poke(iterator);
                    break;
                default:
                    unexpected_character(*iterator);
                    break;
            }
        }
        if(level > 0) {
            unbalanced_statement();
        }
        return end;
    };

    return do_parse();
}

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------
