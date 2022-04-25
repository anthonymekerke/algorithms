/**
 * @file engine.cpp
 * See the AUTHORS or Authors.txt file
 */

#include "engine.hpp"

namespace kikotsoka {

    const Engine::Patterns Engine::PATTERNS = {
            {
                    {{false, false, true},  {false, true,  false}, {true,  false, false}},
                    {{true,  false, false}, {false, true,  false}, {false, false, true}}
            },
            {
                    {{false, true,  false}, {false, true,  false}, {true,  false, true}},
                    {{true,  false, false}, {false, true,  true},  {true,  false, false}},
                    {{true, false, true},  {false, true,  false}, {false, true,  false}},
                    {{false, false, true}, {true,  true,  false}, {false, false, true}}
            },
            {
                    {{false, true,  false}, {true,  true,  false}, {false, true,  true}},
                    {{false, true,  false}, {true,  true,  true},  {true,  false, false}},
                    {{true, true,  false}, {false, true,  true},  {false, true,  false}},
                    {{false, false, true}, {true,  true,  true},  {false, true,  false}}
            },
            {
                    {{true,  true,  false}, {true,  false, true},  {false, true,  true}},
                    {{false, true,  true},  {true,  false, true},  {true,  true,  false}}
            },
            {
                    {{true,  false, true},  {true,  false, true},  {true,  true,  true}},
                    {{true,  true,  true},  {true,  false, false}, {true,  true,  true}},
                    {{true, true,  true},  {true,  false, true},  {true,  false, true}},
                    {{true,  true,  true}, {false, false, true},  {true,  true,  true}}
            }
    };

    const size_t Engine::SIZE = 12;
    const size_t Engine::PAWN_START = 60;

    Engine::Engine()
            :_current_color(Color::BLACK), _board(SIZE), 
            _black_pawn_number(PAWN_START), _white_pawn_number(PAWN_START)
    {
        for (size_t l = 0; l < SIZE; ++l) {
            _board[l] = std::vector<State::Values>(SIZE);
            for (size_t c = 0; c < SIZE; ++c) {
                _board[l][c] = State::VACANT;
            }
        }
    }

    Engine::~Engine() { }

    State::Values Engine::state(const Coordinates& coordinates) const
    {
        return _board[coordinates.column_index()][coordinates.line_index()];
    }

    int Engine::black_pawn_number() const{
        return _black_pawn_number;
    }

    int Engine::white_pawn_number() const{
        return _white_pawn_number;
    }

    bool Engine::move(const Coordinates& coordinates){
        if(state(coordinates) != State::VACANT){
                return false;
        }

        if(current_color() == Color::BLACK){
                _board[coordinates.column_index()][coordinates.line_index()] = State::BLACK;
                decrement_pawn_number(Color::BLACK);
        }

        if(current_color() == Color::WHITE){
                _board[coordinates.column_index()][coordinates.line_index()] = State::WHITE;
                decrement_pawn_number(Color::WHITE);
        }

        return true;
    }

    int Engine::decrement_pawn_number(Color color){
        if(color == Color::BLACK){
                _black_pawn_number--;
                return _black_pawn_number;
        }

        if(color == Color::WHITE){
                _white_pawn_number--;
                return _white_pawn_number;
        }

        return 0;
    }

}
