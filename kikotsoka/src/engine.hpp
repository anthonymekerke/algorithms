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

        int current_color() const {return _current_color;}

        int black_pawn_number() const {return _black_pawn_number;}
        int white_pawn_number() const {return _white_pawn_number;}

        int black_level() const {return _black_level;}
        int white_level() const {return _white_level;}

        int black_score() const {return _black_score;}
        int white_score() const {return _white_score;}

        Coordinates& black_last_move() {return _black_last_move;}
        const Coordinates& black_last_move() const {return _black_last_move;}

        Coordinates& white_last_move() {return _white_last_move;}
        const Coordinates& white_last_move() const {return _white_last_move;}

        void block();
        bool move(const Coordinates& coordinates);
        void aftermove();
        void switch_player();

        std::vector<Coordinates> get_possible_moves() const;

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
        int _black_level;
        int _white_level;
        int _black_score;
        int _white_score;
        Coordinates _black_last_move;
        Coordinates _white_last_move;

        int pawn_number_m(Color color);
        int pawn_number_p(Color color);
        int level(Color color);
        int score(Color color);

        void configure_parameters_checking(const Coordinates& coord, int& cs, int& ce, int& ls, int& le);

        bool match_pattern(int status, int orientation, int l_start, int c_start);
        void lock_pattern(int l_start, int c_start);

        void block_neighboring(const Coordinates& coord);
        void block_potential_patterns(const Coordinates& coord);
        void unblock();
    };
}

#endif