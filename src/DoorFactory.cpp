#include <iostream>
#include "DoorFactory.h"
#include "Game.h"
#include "DoorStandard.h"
#include "DoorEgypt.h"
#include "DoorMaya.h"
#include "DoorHell.h"


Door *DoorFactory::createDoor(const string &type, ShaderManager *shaderManager) {
    if (type == "standard") {
        return new DoorStandard(shaderManager);
    };
    if (type == "egypt") {
        return new DoorEgypt(shaderManager);
    }
    if (type == "maya") {
        return new DoorMaya(shaderManager);
    }
    if (type == "hell") {
        return new DoorHell(shaderManager);
    }
    return nullptr;
}

