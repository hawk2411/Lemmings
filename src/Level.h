#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <string>
#include "Texture.h"
#include "Sprite.h"
#include "VariableTexture.h"
#include "Door.h"
#include "Trapdoor.h"

class Level {

public:

    static Level &currentLevel() {
        static Level currentLevel;

        return currentLevel;
    }

    struct LevelAttributes {
        int numLemmings;
        int goalLemmings;
        int time;

        int releaseRate;
        int minReleaseRate;
        int jobCount[8];

        unique_ptr<Door> _door;
        Trapdoor *trapdoor;

        Texture levelTexture;
        VariableTexture maskedMap;

        glm::vec2 cameraPos;
        glm::vec2 levelSize;
    };

    void createFromFile(const string &file);

    void init();

    LevelAttributes *getLevelAttributes();


private:
    LevelAttributes levelAttributes;

    glm::vec2 doorPos;
    glm::vec2 trapdoorPos;

    string mapTexturePath;
    string mapMaskPath;
};

#endif // _LEVEL_INCLUDE

