//
// Created by hawk on 19.05.21.
//

#ifndef LEMMINGS_DIFFICULTY_H
#define LEMMINGS_DIFFICULTY_H

struct Difficulty {
    enum class Mode {
        FUN_MODE = 0,
        TRICKY_MODE = 1,
        TAXING_MODE = 2
    };

};

#include <string>
#include "Texture.h"
#include "Sprite.h"
#include "VariableTexture.h"
#include "Door.h"
#include "Trapdoor.h"

#endif //LEMMINGS_DIFFICULTY_H
