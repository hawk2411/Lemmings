//
// Created by hawk on 19.05.21.
//

#ifndef LEMMINGS_DIFFICULTY_H
#define LEMMINGS_DIFFICULTY_H

#include <string>
#include "LemmingsException.h"

struct Difficulty {
    enum class Mode {
        FUN_MODE = 0,
        TRICKY_MODE = 1,
        TAXING_MODE = 2
    };

    static std::string convertToString(const Difficulty::Mode &mode) {
        switch (mode) {
            case Mode::FUN_MODE:
                return "fun";
            case Mode::TRICKY_MODE:
                return "tricky";
            case Mode::TAXING_MODE:
                return "taxing";
            default:
                throw LemmingsException("Unknown difficulty level-");
        }
    }

    static int convertToInt(const Difficulty::Mode &mode) {
        switch (mode) {
            case Difficulty::Mode::FUN_MODE:
                return 0;
            case Difficulty::Mode::TRICKY_MODE:
                return 1;
            case Difficulty::Mode::TAXING_MODE:
                return 2;
            default:
                throw LemmingsException("Unknown difficulty level-");
        }
    }
};

#endif //LEMMINGS_DIFFICULTY_H
