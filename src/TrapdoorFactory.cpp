#include "LemmingsException.h"
#include "TrapdoorFactory.h"
#include "TrapdoorStandard.h"
#include "TrapdoorHell.h"

Trapdoor *TrapdoorFactory::createTrapdoor(const string &type, ShaderManager *shaderManager) {
    if (type == "standard") {
        return  new TrapdoorStandard(shaderManager);
    }
    if (type == "hell") {
        return new TrapdoorHell(shaderManager);
    }
    throw LemmingsException("Unknown trap door type.");
}
