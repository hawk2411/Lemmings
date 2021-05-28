#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <string>
#include <iostream>
#include "Texture.h"
#include "Sprite.h"
#include "VariableTexture.h"
#include "Door.h"
#include "Trapdoor.h"
#include "LevelModes.h"
#include "ShaderManager.h"

struct Level {

    Level(ShaderManager *shaderManager, LevelModes::Mode difficulty, int levelNo);
    ~Level(){std::cout << "Level destructor\n";}
    int numLemmings{};
    int goalLemmings{};
    int time{};

    int releaseRate{};
    int minReleaseRate{};
    static const size_t COUNT_JOBS = 8;
    int lemmingsProJob[COUNT_JOBS]{};
    std::unique_ptr<Door> _door;
    std::unique_ptr<Trapdoor> _trapdoor;

    Texture levelTexture;
    VariableTexture maskedMap;

    glm::vec2 cameraPos{};
    glm::vec2 levelSize{};

    glm::vec2 _doorPos{};
    glm::vec2 _trapdoorPos{};

    string _mapTexturePath;
    string _mapMaskPath;
    int _actualLevel;
    LevelModes::Mode _actualMode;

private:
    void initFromFile(const string &file);

    static std::string getFilename(LevelModes::Mode levelMode, int levelNo);
    ShaderManager* _shaderManager;
};

#endif // _LEVEL_INCLUDE

