/**
 * @file state.hpp
 * See the AUTHORS or Authors.txt file
 */

#ifndef KIKOTSOKA_STATE_HPP
#define KIKOTSOKA_STATE_HPP

#include <string>

namespace kikotsoka {

    class State {
    public:
        enum Values {
            VACANT = 0,
            WHITE = 1,
            BLACK = 2,
            LOCK = 3,
            WHITE_LOCK = 4,
            BLACK_LOCK = 5,
            BLOCK = 6
        };

    };

}

#endif