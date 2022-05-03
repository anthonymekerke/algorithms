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
    engine.effect(f4);
    engine.switch_player();
    
    REQUIRE(engine.state(f4) == State::BLACK);
    REQUIRE(engine.state(g5) == State::BLACK);
    REQUIRE(engine.state(h6) == State::BLACK);

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
    engine.effect(f4);
    
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
    engine.effect(f4);

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
    engine.effect(f4);

    REQUIRE(engine.state(f4) == State::BLACK);
    REQUIRE(engine.state(g5) == State::BLACK);
    REQUIRE(engine.state(h6) == State::BLACK);

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
    engine.effect(f4);

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
    engine.effect(f4);
    engine.switch_player();
    engine.move(k9);
    engine.effect(k9);
    
    REQUIRE(engine.state(i7) == State::WHITE);
    REQUIRE(engine.state(j8) == State::WHITE);
    REQUIRE(engine.state(k9) == State::WHITE);

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
        engine.effect(coords);
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

        engine.block_cells();
        engine.move(coords);
        engine.effect(coords);
        engine.switch_player();
    }

    engine.block_cells();

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

        engine.block_cells();
        engine.move(coords);
        engine.effect(coords);
        engine.switch_player();
    }

    engine.block_cells();
    
    coords = Coordinates(5,8); //F9

    REQUIRE(engine.state(coords) == State::BLOCK);
}