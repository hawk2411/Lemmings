#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "LemmingsException.h"

#include "Level.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"
#include "LevelModes.h"

Level::Level(ShaderManager* shaderManager, LevelModes::Mode difficulty, int levelNo): _actualLevel(levelNo), _actualMode(difficulty), _shaderManager(shaderManager) {

    initFromFile(getFilename(difficulty, levelNo));
}

std::string Level::getFilename(LevelModes::Mode levelMode, int levelNo) {
    return "levels/" + LevelModes::convertToString(levelMode) + "-" + to_string(levelNo) + ".txt";
}

void Level::initFromFile(const string &file) {
    ifstream infile(file);

    int lineCount = 0;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        switch (lineCount) {

            case 0: // LEVEL_TYPE(fun, tricky, taxing, mayhem) LEVEL_NUM
            {
                string levelType;
                int levelNum;
                iss >> levelType >> levelNum;

                string levelName = levelType + to_string(levelNum);

                _mapTexturePath = "images/levels/" + levelName + "/map.png";
                _mapMaskPath = "images/levels/" + levelName + "/mask.png";
                break;
            }

            case 1: // NUM_LEMMINGS GOAL_LEMMINGS TIME(secs)
                iss >> numLemmings >> goalLemmings >> time;
                break;

            case 2: //  RELEASE_RATE JOB_COUNT [CLIMBER, FLOATER, EXPLODER, BLOCKER, BUILDER, BASHER, MINER, DIGGER]
                iss >> releaseRate;
                minReleaseRate = releaseRate;
                for(int & lemmingsCount : lemmingsProJob) {
                    iss >> lemmingsCount;
                }
                break;

            case 3: // TRAPDOOR_POS TRAPDOOR_TYPE(standard, hell)
            {
                int trapdoorPosX, trapdoorPosY;
                std::string trapdoorType;
                iss >> trapdoorPosX >> trapdoorPosY >> trapdoorType;

                _trapdoorPos = glm::vec2(trapdoorPosX, trapdoorPosY);
                _trapdoor = std::unique_ptr<Trapdoor>(TrapdoorFactory::createTrapdoor(trapdoorType, _shaderManager));
                break;
            }
            case 4: // DOOR_POS DOOR_TYPE(standard, egypt, maya, hell)
            {
                int doorPosX, doorPosY;
                std::string doorType;
                iss >> doorPosX >> doorPosY >> doorType;

                _doorPos = glm::vec2(doorPosX, doorPosY);
                _door = unique_ptr<Door>(DoorFactory::createDoor(doorType, _shaderManager));
                break;
            }
            case 5: // LEVEL CAMERA POS
                int cameraPosX, cameraPosY;
                iss >> cameraPosX >> cameraPosY;
                cameraPos = glm::vec2(cameraPosX, cameraPosY);
                break;
            case 6: // LEVEL SIZE
                int levelSizeX, levelSizeY;
                iss >> levelSizeX >> levelSizeY;
                levelSize = glm::vec2(levelSizeX, levelSizeY);
                break;
            default:
                break;
        }
        ++lineCount;
    }
    levelTexture.loadFromFile(_mapTexturePath, TEXTURE_PIXEL_FORMAT_RGBA);
    levelTexture.setMinFilter(GL_NEAREST);
    levelTexture.setMagFilter(GL_NEAREST);

    maskedMap.loadFromFile(_mapMaskPath, TEXTURE_PIXEL_FORMAT_L);
    maskedMap.setMinFilter(GL_NEAREST);
    maskedMap.setMagFilter(GL_NEAREST);


    _trapdoor->init();
    _trapdoor->setPosition(_trapdoorPos);

    _door->init();
    _door->setPosition(_doorPos);

}


