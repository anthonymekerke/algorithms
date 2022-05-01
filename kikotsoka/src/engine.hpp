/**
 * @file engine.hpp
 * See the AUTHORS or Authors.txt file
 */

#ifndef KIKOTSOKA_ENGINE_HPP
#define KIKOTSOKA_ENGINE_HPP

#include "color.hpp"
#include "coordinates.hpp"
#include "state.hpp"

#include <memory>
#include <vector>

namespace kikotsoka {

    class Engine {
    public:
        Engine();

        ~Engine();

        State::Values state(const Coordinates& coordinates) const;

        int current_color() const { return _current_color; }

        int black_pawn_number() const;
        int white_pawn_number() const;

        bool move(const Coordinates& coordinates);
        void switch_player();
        void effect(const Coordinates& coord);

        typedef std::vector<bool> PatternLine;
        typedef std::vector<PatternLine> Pattern;
        typedef std::vector<Pattern> LevelPattern;
        typedef std::vector<LevelPattern> Patterns;

        static const Patterns PATTERNS;
        static const size_t SIZE;
        static const size_t PAWN_START;

    private:
        Color _current_color;
        std::vector<std::vector<State::Values> > _board;
        int _black_pawn_number;
        int _white_pawn_number;
        int _black_status;
        int _white_status;

        int decrement_pawn_number(Color color);

        void configure_parameters_checking(const Coordinates& coord, int& cs, int& ce, int& ls, int& le);

        bool match_pattern(Color player, int status, int orientation, int l_start, int c_start);
        void block_pattern(Color player, int l_start, int c_start);
    };
}

#endif