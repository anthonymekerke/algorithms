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
            _black_status(0), _white_status(0)
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
                switch_current_color();
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

    void Engine::switch_current_color(){
        Color opponent_color = current_color() == Color::WHITE ? Color::BLACK : Color::WHITE;

        _current_color = opponent_color;
    }

    void Engine::check_possibilities(const Coordinates& coord){
        int start_column, start_line, end_column, end_line;

        if(coord.column_index() > 1){
            start_column = -2;
        }
        else if(coord.column_index() == 1){
            start_column = -1;
        }
        else if(coord.column_index() == 0){
            start_column = 0;
        }

        if(coord.column_index() < SIZE - 3){
            end_column = 0;
        }
        else if(coord.column_index() == SIZE - 2){
            end_column = -1;
        }
        else if(coord.column_index() == SIZE - 1){
            end_column = -2;
        }

        if(coord.line_index() > 1){
            start_line = -2;
        }
        else if(coord.line_index() == 1){
            start_line = -1;
        }
        else if(coord.line_index() == 0){
            start_line = 0;
        }

        if(coord.line_index() < SIZE - 3){
            end_line = 0;
        }
        else if(coord.line_index() == SIZE - 2){
            end_line = -1;
        }
        else if(coord.line_index() == SIZE - 1){
            end_line = -2;
        }

        for(int i = start_line; i <= end_line; i++){
            for(int j = start_column; j <= end_column; j++){
                bool checked = check_pattern(Color::BLACK, 0, 1, coord.column_index() + i, 
                    coord.line_index() + j);

                if(checked){
                    std::cout<<"pattern verified"<<std::endl;
                    block_pattern(Color::BLACK, coord.column_index() + i, coord.line_index()+j);
                }
            }
        }
    }

    bool Engine::check_pattern(Color player, int s, int o, int c_start, int l_start){
        State::Values state_to_check = player == Color::BLACK ? State::BLACK : State::WHITE;
        int checked_cells = 0;

        std::cout << "start: "<< "[" << c_start << ";" << l_start << "]" << std::endl;

        for(int l = 0; l < 3; l++){
            std::cout << "[";
            for(int c = 0; c < 3; c++){
                std::cout << "[" << c+c_start << ";" << l+l_start << "]";
                if((PATTERNS[s][o][l][c] == false && _board[c+c_start][l+l_start] == State::VACANT) ||
                (PATTERNS[s][o][l][c] == true && _board[c+c_start][l+l_start] == state_to_check))
                {
                    checked_cells++;
                }
            }
            std::cout<<"]"<<std::endl;
        }
        std::cout<<std::endl;

        return checked_cells == 9;
    }

    void Engine::block_pattern(Color player, int c_start, int l_start){
        State::Values state_to_check = player == Color::BLACK ? State::BLACK : State::WHITE;

        for(int l = 0; l < 3; l++){
            for(int c = 0; c < 3; c++){
                if(_board[c_start+c][l_start+l] != state_to_check){
                    _board[c_start+c][l_start+l] = State::BLOCK;
                }
            }
        }
    }

}
