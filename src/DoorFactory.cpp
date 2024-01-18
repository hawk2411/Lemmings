#include <iostream>
#include "DoorFactory.h"
#include "DoorStandard.h"
#include "DoorEgypt.h"
#include "DoorMaya.h"
#include "DoorHell.h"


std::unique_ptr<Door> DoorFactory::createDoor(const string &type, ShaderManager *shaderManager) {
    if (type == "standard") {
        return std::make_unique<DoorStandard>(shaderManager);
    }
    if (type == "egypt") {
        return std::make_unique<DoorEgypt>(shaderManager);
    }
    if (type == "maya") {
        return std::make_unique<DoorMaya>(shaderManager);
    }
    if (type == "hell") {
        return std::make_unique<DoorHell>(shaderManager);
    }
    return nullptr;
}

