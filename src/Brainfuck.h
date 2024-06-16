/*
 * Brainfuck.h - Copyright (c) 2024 - Olivier Poncet
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
#ifndef __Brainfuck_h__
#define __Brainfuck_h__

// ---------------------------------------------------------------------------
// bf::State
// ---------------------------------------------------------------------------

namespace bf {

class State
{
public: // public interface
    State();

    State(const State&) = delete;

    State& operator=(const State&) = delete;

   ~State() = default;

    uint32_t next();

    uint32_t prev();

    uint8_t  incr();

    uint8_t  decr();

    uint8_t  peek();

    uint8_t  poke(const uint8_t value);

private: // private data
    uint8_t        _value[32768];
    uint32_t const _count;
    uint32_t       _index;
};

}

// ---------------------------------------------------------------------------
// bf::Interpreter
// ---------------------------------------------------------------------------

namespace bf {

class Interpreter
{
public: // public interface
    Interpreter() = default;

    Interpreter(const Interpreter&) = delete;

    Interpreter& operator=(const Interpreter&) = delete;

   ~Interpreter() = default;

    void eval(const std::string& expression);

private: // private interface
    const char* parse(State& state, const char* begin, const char* end, const int level, const bool execute);

private: // private static data
    static constexpr char TOK_CR      = '\r';
    static constexpr char TOK_LF      = '\n';
    static constexpr char TOK_TAB     = '\t';
    static constexpr char TOK_SPACE   = ' ';
    static constexpr char TOK_COMMENT = '#';
    static constexpr char TOK_BEG     = '[';
    static constexpr char TOK_END     = ']';
    static constexpr char TOK_NEXT    = '>';
    static constexpr char TOK_PREV    = '<';
    static constexpr char TOK_INCR    = '+';
    static constexpr char TOK_DECR    = '-';
    static constexpr char TOK_PEEK    = '.';
    static constexpr char TOK_POKE    = ',';
};

}

// ---------------------------------------------------------------------------
// End-Of-File
// ---------------------------------------------------------------------------

#endif /* __Brainfuck_h__ */
