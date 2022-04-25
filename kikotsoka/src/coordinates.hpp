/**
 * @file coordinates.hpp
 * See the AUTHORS or Authors.txt file
 */

#ifndef KIKOTSOKA_COORDINATES_HPP
#define KIKOTSOKA_COORDINATES_HPP

#include <string>

namespace kikotsoka {

    class Coordinates {
    public:
        explicit Coordinates(int = -1, int = -1);

        char column() const { return char('A' + _column); }

        int column_index() const { return _column; }

        int line() const { return _line + 1; }

        int line_index() const { return _line; }

        bool operator==(const Coordinates& coordinates) const
        {
            return line() == coordinates.line() and column() == coordinates.column();
        }

        std::string to_string() const { return char('A' + _column) + std::to_string(_line + 1); }

    private:
        int _column;
        int _line;
    };

}

#endif