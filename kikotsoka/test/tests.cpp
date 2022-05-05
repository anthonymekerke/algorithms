/**
 * @file tests.cpp
 * See the AUTHORS or Authors.txt file
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../src/coordinates.hpp"
#include "../src/engine.hpp"

using namespace kikotsoka;

TEST_CASE("storie 1", "to_string")
{
    const Coordinates coordinates(0, 0);
    const std::string str = coordinates.to_string();

    REQUIRE(str == "A1");
}

TEST_CASE("storie 1 bis", "has column and line")
{
    const Coordinates coordinates(2, 4);

    REQUIRE(coordinates.column() == 'C');
    REQUIRE(coordinates.line() == 5);
}

TEST_CASE("storie 2", "coordinates equality")
{
    const Coordinates c1(2, 1);
    const Coordinates c2(2, 1);
    const Coordinates c3(7, 2);
    const Coordinates c4(2, 3);

    REQUIRE(c1 == c2);
    REQUIRE(c2 == c1);
    REQUIRE_FALSE(c1 == c3);
    REQUIRE_FALSE(c1 == c4);
}

TEST_CASE("storie 3", "has 144 empty cells")
{
    const Engine engine;

    REQUIRE(Engine::SIZE == 12);
    for (size_t l = 0; l < Engine::SIZE; ++l) {
        for (size_t c = 0; c < Engine::SIZE; ++c) {
            REQUIRE(engine.state(Coordinates(l, c)) == State::VACANT);
        }
    }
}

TEST_CASE("storie 4", "black starts")
{
    const Engine engine;

    REQUIRE(engine.current_color() == Color::BLACK);
}

TEST_CASE("storie 5", "start pawn number")
{
    const Engine engine;

    REQUIRE(engine.black_pawn_number() == 60);
    REQUIRE(engine.white_pawn_number() == 60);
}

TEST_CASE("storie 6", "black first move")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);

    REQUIRE(h6.column() == 'H');
    REQUIRE(h6.line() == 6);

    engine.move(h6);
    engine.switch_player();

    REQUIRE(engine.state(h6) != State::VACANT);
    REQUIRE(engine.state(h6) == State::BLACK);
}

TEST_CASE("storie 7", "black 59 pawn left")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);

    engine.move(h6);
    engine.switch_player();

    REQUIRE(engine.black_pawn_number() == 59);
}

TEST_CASE("storie 8", "white has to play")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);

    engine.move(h6);
    engine.switch_player();

    REQUIRE(engine.current_color() == Color::WHITE);
}

TEST_CASE("storie 9", "white first move")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);
    Coordinates i7 = Coordinates(8, 6);

    engine.move(h6);
    engine.switch_player();
    engine.move(i7);
    engine.switch_player();

    REQUIRE(i7.column() == 'I');
    REQUIRE(i7.line() == 7);

    REQUIRE(engine.state(i7) != State::VACANT);
    REQUIRE(engine.state(i7) == State::WHITE);
    REQUIRE(engine.white_pawn_number() == 59);
}

TEST_CASE("storie 10", "cells blocked after pattern")
{
    Engine engine;

    /*
    Moves: N-H6, B-I7, N-G5, B-J8, N-F4
    */
    Coordinates h6 = Coordinates(7,5);
    Coordinates i7 = Coordinates(8,6);
    Coordinates g5 = Coordinates(6,4);
    Coordinates j8 = Coordinates(9,7);
    Coordinates f4 = Coordinates(5,3);

    Coordinates f5 = Coordinates(5,4);
    Coordinates f6 = Coordinates(5,5);
    Coordinates g4 = Coordinates(6,3);
    Coordinates g6 = Coordinates(6,5);
    Coordinates h4 = Coordinates(7,3);
    Coordinates h5 = Coordinates(7,4);

    engine.move(h6);
    engine.switch_player();
    engine.move(i7);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(j8);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();
    engine.switch_player();
    
    REQUIRE(engine.state(f4) == State::BLACK_LOCK);
    REQUIRE(engine.state(g5) == State::BLACK_LOCK);
    REQUIRE(engine.state(h6) == State::BLACK_LOCK);

    REQUIRE(engine.state(f5) == State::LOCK);
    REQUIRE(engine.state(f6) == State::LOCK);
    REQUIRE(engine.state(g4) == State::LOCK);
    REQUIRE(engine.state(g6) == State::LOCK);
    REQUIRE(engine.state(h4) == State::LOCK);
    REQUIRE(engine.state(h5) == State::LOCK);
}

TEST_CASE("storie 11", "black goes level 1")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);
    Coordinates i7 = Coordinates(8,6);
    Coordinates g5 = Coordinates(6,4);
    Coordinates j8 = Coordinates(9,7);
    Coordinates f4 = Coordinates(5,3);

    REQUIRE(engine.black_level() == 0);

    engine.move(h6);
    engine.switch_player();
    engine.move(i7);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(j8);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();
    
    REQUIRE(engine.black_level() == 1);
}

TEST_CASE("storie 12", "black takes 2 pawns from white")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);
    Coordinates h5 = Coordinates(7,4);
    Coordinates g5 = Coordinates(6,4);
    Coordinates g4 = Coordinates(6,3);
    Coordinates f4 = Coordinates(5,3);

    engine.move(h6);
    engine.switch_player();
    engine.move(h5);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(g4);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();

    REQUIRE(engine.black_pawn_number() == 59);
    REQUIRE(engine.white_pawn_number() == 58);
}

TEST_CASE("storie 13", "cells blocked after pattern, white pawns taken")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);
    Coordinates h5 = Coordinates(7,4);
    Coordinates g5 = Coordinates(6,4);
    Coordinates g4 = Coordinates(6,3);
    Coordinates f4 = Coordinates(5,3);

    Coordinates h4 = Coordinates(7,3);
    Coordinates g6 = Coordinates(6,5);
    Coordinates f5 = Coordinates(5,4);
    Coordinates f6 = Coordinates(5,5);

    engine.move(h6);
    engine.switch_player();
    engine.move(h5);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(g4);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();

    REQUIRE(engine.state(f4) == State::BLACK_LOCK);
    REQUIRE(engine.state(g5) == State::BLACK_LOCK);
    REQUIRE(engine.state(h6) == State::BLACK_LOCK);

    REQUIRE(engine.state(h5) == State::LOCK);
    REQUIRE(engine.state(g4) == State::LOCK);
    REQUIRE(engine.state(h4) == State::LOCK);
    REQUIRE(engine.state(g6) == State::LOCK);
    REQUIRE(engine.state(f5) == State::LOCK);
    REQUIRE(engine.state(f6) == State::LOCK);
}

TEST_CASE("storie 14", "Black get 2 points")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);
    Coordinates h5 = Coordinates(7,4);
    Coordinates g5 = Coordinates(6,4);
    Coordinates g4 = Coordinates(6,3);
    Coordinates f4 = Coordinates(5,3);

    engine.move(h6);
    engine.switch_player();
    engine.move(h5);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(g4);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();

    REQUIRE(engine.black_score() == 2);
}

TEST_CASE("storie 15", "White makes first pattern")
{
    Engine engine;

    Coordinates h6 = Coordinates(7,5);
    Coordinates i7 = Coordinates(8,6);
    Coordinates g5 = Coordinates(6,4);
    Coordinates j8 = Coordinates(9,7);
    Coordinates f4 = Coordinates(5,3);
    Coordinates k9 = Coordinates(10,8);

    Coordinates i8 = Coordinates(8,7);
    Coordinates i9 = Coordinates(8,8);
    Coordinates j7 = Coordinates(9,6);
    Coordinates j9 = Coordinates(9,8);
    Coordinates k7 = Coordinates(10,6);
    Coordinates k8 = Coordinates(10,7);

    engine.move(h6);
    engine.switch_player();
    engine.move(i7);
    engine.switch_player();
    engine.move(g5);
    engine.switch_player();
    engine.move(j8);
    engine.switch_player();
    engine.move(f4);
    engine.aftermove();
    engine.switch_player();
    engine.move(k9);
    engine.aftermove();
    
    REQUIRE(engine.state(i7) == State::WHITE_LOCK);
    REQUIRE(engine.state(j8) == State::WHITE_LOCK);
    REQUIRE(engine.state(k9) == State::WHITE_LOCK);

    REQUIRE(engine.state(i8) == State::LOCK);
    REQUIRE(engine.state(i9) == State::LOCK);
    REQUIRE(engine.state(j7) == State::LOCK);
    REQUIRE(engine.state(j9) == State::LOCK);
    REQUIRE(engine.state(k7) == State::LOCK);
    REQUIRE(engine.state(k8) == State::LOCK);

    REQUIRE(engine.white_pawn_number() == 57);
    REQUIRE(engine.white_level() == 1);
    REQUIRE(engine.white_score() == 0);
}


TEST_CASE("storie 16", "black form second pattern")
{
    Engine engine;
    Coordinates coords;

    /*
    Moves: N-H6, B-I7, N-G5, B-J8, N-F4, B-K9, N-A1, B-A3, N-C1, B-C3, N-B2, B-B5, N-B3  
    */
    std::vector<int> columns = {7,8,6,9,5,10,0,0,2,2,1,1,1};
    std::vector<int> lines   = {5,6,4,7,3,8,0,2,0,2,1,4,2};

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.move(coords);
        engine.aftermove();
        engine.switch_player();
    }

    REQUIRE(engine.black_level() == 2);
    REQUIRE(engine.black_score() == 2);
    REQUIRE(engine.black_pawn_number() == 55);
}

TEST_CASE("storie 17", "White last move blocks black")
{
    Engine engine;
    Coordinates coords;

    /*
    Moves: N-H6, B-I7, N-G5, B-J8, N-F4, B-K9, N-A1, B-A3, N-C1, B-C3, N-B2, B-B4  
    */
    std::vector<int> columns = {7,8,6,9,5,10,0,0,2,2,1,1};
    std::vector<int> lines   = {5,6,4,7,3,8,0,2,0,2,1,3};

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.block();
        engine.move(coords);
        engine.aftermove();
        engine.switch_player();
    }

    engine.block();

    Coordinates b3 = Coordinates(1, 2);
    Coordinates a4 = Coordinates(0, 3);
    Coordinates c4 = Coordinates(2, 3);
    Coordinates b5 = Coordinates(1, 4);

    REQUIRE(engine.state(b3) == State::BLOCK);
    REQUIRE(engine.state(a4) == State::BLOCK);
    REQUIRE(engine.state(c4) == State::BLOCK);
    REQUIRE(engine.state(b5) == State::BLOCK);
}

TEST_CASE("storie 18", "can't form lower pattern")
{
    Engine engine;
    Coordinates coords;

    /*
    Moves: N-H6, B-I7, N-G5, B-J8, N-F4, B-K9, N-H7, B-J4, N-G8, B-J5, try: N-F9
    */
    std::vector<int> columns = {7,8,6,9,5,10,7,9,6,9};
    std::vector<int> lines   = {5,6,4,7,3,8,6,3,7,4};

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.block();
        engine.move(coords);
        engine.aftermove();
        engine.switch_player();
    }

    engine.block();
    
    coords = Coordinates(5,8); //F9

    REQUIRE(engine.state(coords) == State::BLOCK);
}

TEST_CASE("storie 19", "white form Ko, black can't play F8")
{
    Engine engine;
    Coordinates coords;
    /*
    Moves: N-H6, B-I7, N-G5, B-J8, N-F4, B-K9, N-H7, B-J4, N-G8, B-J5,
            N-G9, B-I6, N-H8, B-K6.
    Try: N-F8.
    */
    std::vector<int> columns = {7,8,6,9,5,10,7,9,6,9,6,8,7,10};
    std::vector<int> lines   = {5,6,4,7,3,8,6,3,7,4,8,5,7,5};

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.block();
        engine.move(coords);
        engine.aftermove();
        engine.switch_player();
    }

    engine.block();

    Coordinates i4 = Coordinates(8, 3);
    Coordinates i5 = Coordinates(8, 4);
    Coordinates i6 = Coordinates(8, 5);
    Coordinates j4 = Coordinates(9, 3);
    Coordinates j5 = Coordinates(9, 4);
    Coordinates j6 = Coordinates(9, 5);
    Coordinates k4 = Coordinates(10, 3);
    Coordinates k5 = Coordinates(10, 4);
    Coordinates k6 = Coordinates(10, 5);
    Coordinates f8 = Coordinates(5, 7);

    REQUIRE(engine.state(i4) == State::LOCK);
    REQUIRE(engine.state(i5) == State::LOCK);
    REQUIRE(engine.state(i6) == State::WHITE_LOCK);
    REQUIRE(engine.state(j4) == State::WHITE_LOCK);
    REQUIRE(engine.state(j5) == State::WHITE_LOCK);
    REQUIRE(engine.state(j6) == State::LOCK);
    REQUIRE(engine.state(k4) == State::LOCK);
    REQUIRE(engine.state(k5) == State::LOCK);
    REQUIRE(engine.state(k6) == State::WHITE_LOCK);

    REQUIRE(engine.state(f8) == State::BLOCK);
}

TEST_CASE("storie 20", "Black win, score(B-W): 3-1")
{
    Engine engine;
    Coordinates coords;

    /*
    Moves: B-E12;W-D12;B-G9;W-I2;B-G12;W-E3;B-I9;W-J12;B-J2;
            W-B11;B-H12;W-A12;B-H2;W-H1;B-D1;W-F12;
            B-I10;W-G8;B-L10;W-E5;B-E7;W-D10;B-D7;W-K12;B-I6;
            W-L11;B-F6;W-L5;B-F5;W-H9;B-A11;W-A6;B-I11;W-H6;
            B-D8;W-B2;B-L7;W-E11;B-B9;W-B1;B-J10;W-B5;B-D6;W-J7;
            B-G4;W-C2;B-I3;W-K7;B-A2;W-H4;B-C5;W-J11;B-A7;
            W-I1;B-G10;W-A3;B-B3;W-L1;B-F8;W-I4;B-L4;W-E2;B-L3;
            W-F4;B-H11;W-A5;B-B7;W-K2;B-K10;W-I8;B-C7;
            W-L9;B-E4;W-K4;B-H5;W-F2;B-G11;W-G2;B-C6;W-D11;B-A1;
            W-J6;B-J3;W-E1;B-J5;W-A9;B-F10;W-J1;B-C12;
            W-L6;B-A8;W-F1;B-K3;W-F11;B-A4;W-G3;B-L8;W-K11;
            B-L2;W-C11;B-C8;W-I12;B-C4;W-K6
    */
    std::vector<int> columns = 
    { 
        4,3,6,8,6,4,8,9,9,
        1,7,0,7,7,3,5,
        8,6,11,4,4,3,3,10,8,
        11,5,11,5,7,0,0,8,7,
        3,1,11,4,1,1,9,1,3,9,
        6,2,8,10,0,7,2,9,0,
        8,6,0,1,11,5,8,11,4,11,
        5,7,0,1,10,10,8,2,
        11,4,10,7,5,6,6,2,3,0,
        9,9,4,9,0,5,9,2,
        11,0,5,10,5,0,6,11,10,
        11,2,2,8,2,10
    };
    std::vector<int> lines   = 
    {
        11,11,8,1,11,2,8,11,1,
        10,11,11,1,0,0,11,
        9,7,9,4,6,9,6,11,5,
        10,5,4,4,8,10,5,10,5,
        7,1,6,10,8,0,9,4,5,6,
        3,1,2,6,1,3,4,10,6,
        0,9,2,2,0,7,3,3,1,2,
        3,10,4,6,1,9,7,6,
        8,3,3,4,1,10,1,5,10,0,
        5,2,0,4,8,9,0,11,
        5,7,0,2,10,3,2,7,10,
        1,10,7,11,3,5
    };

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.block();
        engine.move(coords);
        engine.aftermove();

        engine.switch_player();
    }

    REQUIRE(engine.black_level() == 2);
    REQUIRE(engine.black_score() == 3);
    REQUIRE(engine.white_score() == 1);
}

TEST_CASE("storie 21", "White win, score(B-W): 1-4")
{
    Engine engine;
    Coordinates coords;

    /* Moves: B-C6;W-I6;B-A6;W-G4;B-B10;W-J10;B-H12;W-A7;B-K10;W-C10;B-J5;
        W-I5;B-L5;W-A1;B-H4;W-D5;B-J3;W-D12;B-D8;W-J6;B-D10;W-C2;B-F8;
        W-A4;B-E4;W-I8;B-B2;W-G3;B-C9;W-B12;B-B4;W-E3;B-I12;W-E6;B-K12;
        W-L9;B-J1;W-L11;B-J12;W-J8;B-C1;W-E12;B-G1;W-E11;B-H5;W-B1;
        B-H10;W-D3;B-G9;W-L1;B-H7;W-F6;B-B8;W-I9;B-F3;W-L3;B-C11;W-G7;B-E2;
        W-K2;B-B7;W-G2;B-A12;W-L4;B-K1;W-F5;B-K4;W-I2;B-E1;W-A10;B-K6;W-H3;
        B-E9;W-C12;B-D6;W-L7;B-J7;W-I11;B-H1;W-K11;B-K5;W-I1;B-G12;W-E8;
        B-C5;W-E7;B-K3;W-D11;B-L2;W-K7;B-D4;W-A3;B-H11;W-A5;B-F7;W-K9;B-J11;
        W-A11;B-F11;W-D7;B-J2;W-L10;B-H2;W-E10;B-G5;W-D9;B-@;W-A2;B-@;W-J4;B-@;W-C4
    */

    std::vector<int> columns = 
    {
        2,8,0,6,1,9,7,0,10,2,9,
        8,11,0,7,3,9,3,3,9,3,2,5,
        0,1,8,1,6,2,1,1,4,8,4,10,
        11,9,11,9,9,2,4,6,4,7,1,
        7,3,6,11,7,5,1,8,5,11,2,6,4,
        10,1,6,0,11,10,5,10,8,4,0,10,7,
        4,2,3,11,9,8,7,10,10,8,6,4,
        2,4,10,3,11,10,3,0,7,0,4,10,9,
        0,5,3,9,11,7,4,6,3,-1,0,-1,9,-1,2
    };
    std::vector<int> lines   = 
    {
        5,5,5,3,9,9,11,6,9,9,4,
        4,4,0,3,4,2,11,7,5,9,1,7,
        3,3,7,1,2,8,11,3,2,11,5,11,
        8,0,10,11,7,0,11,0,10,4,0,
        9,2,8,0,6,5,7,8,2,2,10,6,1,
        1,6,1,11,3,0,4,3,1,0,9,5,2,
        8,11,5,6,6,10,0,10,4,0,11,7,
        4,6,2,10,1,6,3,2,10,4,6,8,10,
        10,10,6,1,9,1,9,4,8,-1,1,-1,3,-1,3
    };

    std::vector<Coordinates> possible_moves;

    for(size_t i = 0; i < columns.size(); ++i){
        coords = Coordinates(columns[i], lines[i]);

        engine.block();

        possible_moves = engine.get_possible_moves();

        if(!possible_moves.empty()){
            engine.move(coords);
            engine.aftermove();
        }        

        engine.switch_player();
    }

    REQUIRE(engine.white_level() == 2);
    REQUIRE(engine.white_score() == 4);
    REQUIRE(engine.black_score() == 1);
}

TEST_CASE("storie 22")
{
    /* Moves:
        BB1 ;WJ11 ;BH5 ;WI11 ;BJ12 ;WD6 ;BD11 ;WH11 ;BG3 ;WC5 ;BE7 ;
        WG1 ;BH10 ;WL2 ;BC3 ;WD2 ;BF7 ;WK1 ;BL4 ;WI2 ;BB9 ;WE11 ;BC1 ;
        WD9 ;BE3 ;WC11 ;BL9 ;WB4 ;BC8 ;WJ10 ;BE8 ;WF2 ;BL10 ;WK10 ;BG4 ;
        WA4 ;BE2 ;WE6 ;BA11 ;WD8 ;BL7 ;WH3 ;BG10 ;WI3 ;BB3 ;WA7 ;BG7 ;
        WG11 ;BJ5 ;WI10 ;BK2 ;WE10 ;BJ7 ;WC12 ;BI6 ;WD3 ;BF6 ;WG12 ;BB7 ;
        WF1 ;BA5 ;WJ4 ;BC2 ;WG9 ;BF12 ;WK4 ;BC9 ;WH7 ;BB2 ;WB11 ;BH8 ;WE5 ;
        BK7 ;WE9 ;BC10 ;WF5 ;BB8 ;WI7 ;BK6 ;WC7 ;BJ1 ;WF11 ;BF4 ;WA8 ;BB10 ;
        WE4 ;BI1 ;WA12 ;BA6 ;WH1 ;BJ2 ;WA3 ;BD1 ;WA9 ;BF3 ;WI9 ;BD12 ;WA1 ;
        BK9 ;WJ6 ;BJ9 ;WG8 ;BK12 ;WL1 ;BL5 ;WA2 ;BD7
    */
}

TEST_CASE("storie 23")
{
    /* Moves:
        BA8 ;WC2 ;BC10 ;WG8 ;BB9 ;WK9 ;BD8 ;WF9 ;BE10 ;WB6 ;BF8 ;WG6 ;
        BE9 ;WJ4 ;BE4 ;WK3 ;BD5 ;WG10 ;BE3 ;WC1 ;BF4 ;WH4 ;BD4 ;WI3 ;BJ8 ;
        WC7 ;BJ7 ;WG3 ;BI7 ;WL4 ;BH8 ;WD2 ;BH7 ;WJ9 ;BI9 ;WD6 ;BH9 ;WK7 ;
        BJ12 ;WG7 ;BK11 ;WF1 ;BK12 ;WH6 ;BI10 ;WL7 ;BK10 ;WC5 ;BJ10 ;WE12 ;BI12
    */
}

    /*
    for(int i = 0; i < 12; ++i){
        for(int j = 0; j < 12; ++j){
            coords = Coordinates(j,i);
            std::cout<<engine.state(coords)<<" ";
        }std::cout<<std::endl;
    }std::cout<<std::endl;

        if(engine.current_color() == Color::BLACK){
            for(int i = 0; i < 12; ++i){
                for(int j = 0; j < 12; ++j){
                    coords = Coordinates(j,i);
                    std::cout<<engine.state(coords)<<" ";
                }std::cout<<std::endl;
            }std::cout<<std::endl;
        }
    */