/**
 * @file engine.cpp
 * See the AUTHORS or Authors.txt file
 */

#include "engine.hpp"
#include <iostream>

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
            _black_pawn_number(PAWN_START), _white_pawn_number(PAWN_START),
            _black_level(0), _white_level(0)
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

        Color current_col = current_color() == Color::WHITE ? Color::WHITE : Color::BLACK;
        State::Values current_state = current_col == Color::WHITE ? State::WHITE : State::BLACK;

        if(current_col == Color::BLACK || current_col == Color::WHITE){
            _board[coordinates.column_index()][coordinates.line_index()] = current_state;
            decrement_pawn_number(current_col);
            return true;
        }

        return false;
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

    void Engine::switch_player(){
        Color opponent_color = current_color() == Color::WHITE ? Color::BLACK : Color::WHITE;

        _current_color = opponent_color;
    }

    void Engine::configure_parameters_checking(const Coordinates& coord, 
            int& cs, int& ce, int& ls, int& le, int& level)
    {
        if(coord.column_index() > 1) {cs = -2;}
        else if(coord.column_index() == 1) {cs = -1;}
        else if(coord.column_index() == 0) {cs = 0;}

        if(coord.column_index() < SIZE - 3) {ce = 0;}
        else if(coord.column_index() == SIZE - 2) {ce = -1;}
        else if(coord.column_index() == SIZE - 1) {ce = -2;}

        if(coord.line_index() > 1) {ls = -2;}
        else if(coord.line_index() == 1) {ls = -1;}
        else if(coord.line_index() == 0) {ls = 0;}

        if(coord.line_index() < SIZE - 3) {le = 0;}
        else if(coord.line_index() == SIZE - 2) {le = -1;}
        else if(coord.line_index() == SIZE - 1) {le = -2;}

        if(current_color() == Color::BLACK) {level = black_level();}
        else if(current_color() == Color::WHITE) {level = white_level();}
    }

    void Engine::effect(const Coordinates& coord){
        int c_start, c_end, l_start, l_end, level, orientation = 1;
        bool pattern_matching;

        configure_parameters_checking(coord, c_start, c_end, l_start, l_end, level);

        for(int c = c_start; c <= c_end; c++){
            for(int l = l_start; l <= l_end; l++){
                pattern_matching = match_pattern(_current_color, level, orientation, coord.column_index() + c, coord.line_index() + l);

                if(pattern_matching){
                    block_pattern(_current_color, coord.column_index() + c, coord.line_index()+l);
                    increment_level(_current_color);
                }
            }
        }
    }

    bool Engine::match_pattern(Color player, int s, int o, int c_start, int l_start){
        State::Values state_player = player == Color::BLACK ? State::BLACK : State::WHITE;
        State::Values state_opponent = player == Color::BLACK ? State::WHITE : State::BLACK;
        int checked_cells = 0;

        for(int l = 0; l < 3; l++){
            for(int c = 0; c < 3; c++){
                if((PATTERNS[s][o][l][c] == false && 
                        (_board[c+c_start][l+l_start] == State::VACANT || 
                        _board[c+c_start][l+l_start] == state_opponent)) ||
                    (PATTERNS[s][o][l][c] == true && 
                        _board[c+c_start][l+l_start] == state_player))
                {
                    checked_cells++;
                }
            }
        }

        return checked_cells == 9;
    }

    void Engine::block_pattern(Color player, int c_start, int l_start){
        State::Values state_player = player == Color::BLACK ? State::BLACK : State::WHITE;
        State::Values state_opponent = player == Color::BLACK ? State::WHITE : State::BLACK;

        for(int l = 0; l < 3; l++){
            for(int c = 0; c < 3; c++){
                if(_board[c_start+c][l_start+l] == state_opponent){
                    increment_pawn_number(player);
                }
                if(_board[c_start+c][l_start+l] != state_player){
                    _board[c_start+c][l_start+l] = State::BLOCK;
                }
            }
        }
    }

    int Engine::increment_level(Color color){
        if(color == Color::BLACK){
            _black_level++;
            return _black_level;
        }

        if(color == Color::WHITE){
            _white_level++;
            return _black_level;
        }

        return -1;
    }

    int Engine::black_level() const {return _black_level;}

    int Engine::white_level() const {return _white_level;}

    int Engine::increment_pawn_number(Color color){
        if(color == Color::BLACK){
            _black_pawn_number++;
            return _black_pawn_number;
        }

        if(color == Color::WHITE){
            _white_pawn_number++;
            return _white_pawn_number;
        }

        return 0;
    }

}
