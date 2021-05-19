#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <string>
#include "Texture.h"
#include "Sprite.h"
#include "VariableTexture.h"
#include "Door.h"
#include "Trapdoor.h"
#include "Difficulty.h"


struct Level {

    Level(Difficulty::Mode difficulty, int levelNo);

    static Level &currentLevel() {
        static Level currentLevel;

        return currentLevel;
    }
    int numLemmings{};
    int goalLemmings{};
    int time{};

    int releaseRate{};
    int minReleaseRate{};
    static const size_t COUNT_JOBS = 8;
    int lemmingsProJob[COUNT_JOBS]{};
    std::unique_ptr<Door> _door;
    std::unique_ptr<Trapdoor> trapdoor;

    Texture levelTexture;
    VariableTexture maskedMap;

    glm::vec2 cameraPos{};
    glm::vec2 levelSize{};

    glm::vec2 _doorPos{};
    glm::vec2 _trapdoorPos{};

    string _mapTexturePath;
    string _mapMaskPath;
    int _actualLevel;
    Level::Mode _actualMode;

private:
    void initFromFile(const string &file);

    static std::string getFilename(Difficulty::Mode levelMode, int levelNo);
};

#endif // _LEVEL_INCLUDE

