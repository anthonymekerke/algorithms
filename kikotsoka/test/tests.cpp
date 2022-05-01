/**
 * @file tests.cpp
 * See the AUTHORS or Authors.txt file
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../src/coordinates.hpp"
#include "../src/engine.hpp"

using namespace kikotsoka;

TEST_CASE("to_string", "coordinates")
{
    const Coordinates coordinates(0, 0);
    const std::string str = coordinates.to_string();

    REQUIRE(str == "A1");
}

TEST_CASE("has column and line", "coordinates")
{
    const Coordinates coordinates(2, 4);

    REQUIRE(coordinates.column() == 'C');
    REQUIRE(coordinates.line() == 5);
}

TEST_CASE("coordinates equality", "coordinates")
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

TEST_CASE("has 144 empty cells", "engine")
{
    const Engine engine;

    REQUIRE(Engine::SIZE == 12);
    for (size_t l = 0; l < Engine::SIZE; ++l) {
        for (size_t c = 0; c < Engine::SIZE; ++c) {
            REQUIRE(engine.state(Coordinates(l, c)) == State::VACANT);
        }
    }
}

TEST_CASE("black starts", "game")
{
    const Engine engine;

    REQUIRE(engine.current_color() == Color::BLACK);
}

TEST_CASE("start pawn number", "game")
{
    const Engine engine;

    REQUIRE(engine.black_pawn_number() == 60);
    REQUIRE(engine.white_pawn_number() == 60);
}

TEST_CASE("black first move","game")
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

TEST_CASE("black 59 pawn left", "game")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);

    engine.move(h6);
    engine.switch_player();

    REQUIRE(engine.black_pawn_number() == 59);
}

TEST_CASE("white has to play", "game")
{
    Engine engine;
    Coordinates h6 = Coordinates(7,5);

    engine.move(h6);
    engine.switch_player();

    REQUIRE(engine.current_color() == Color::WHITE);
}

TEST_CASE("white first move", "game")
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

TEST_CASE("cells blocked after pattern", "game")
{
    Engine engine;
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

    REQUIRE(engine.state(f5) == State::BLOCK);
    REQUIRE(engine.state(f6) == State::BLOCK);
    REQUIRE(engine.state(g4) == State::BLOCK);
    REQUIRE(engine.state(g6) == State::BLOCK);
    REQUIRE(engine.state(h4) == State::BLOCK);
    REQUIRE(engine.state(h5) == State::BLOCK);
}

TEST_CASE("black goes level 1", "game")
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

TEST_CASE("black takes 2 pawns from white", "game")
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