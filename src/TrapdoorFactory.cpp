#include <iostream>
#include "LemmingsException.h"
#include "TrapdoorFactory.h"
#include "Game.h"
#include "TrapdoorStandard.h"
#include "TrapdoorHell.h"

Trapdoor *TrapdoorFactory::createTrapdoor(const string& type) {
    Trapdoor *trapdoor;
    if (type == "standard") {
        return  new TrapdoorStandard();
    }
    if (type == "hell") {
        return new TrapdoorHell();
    }
    throw LemmingsException("Unknown trap door type.");
}
