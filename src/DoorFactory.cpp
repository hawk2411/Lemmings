#include <iostream>
#include "DoorFactory.h"
#include "Game.h"
#include "DoorStandard.h"
#include "DoorEgypt.h"
#include "DoorMaya.h"
#include "DoorHell.h"


Door *DoorFactory::createDoor(const string &type) {
    if (type == "standard") {
        return new DoorStandard();
    };
    if (type == "egypt") {
        return new DoorEgypt();
    }
    if (type == "maya") {
        return new DoorMaya();
    }
    if (type == "hell") {
        return new DoorHell();
    }
    return nullptr;
}
