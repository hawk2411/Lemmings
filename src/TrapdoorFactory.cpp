#include "LemmingsException.h"
#include "TrapdoorFactory.h"
#include "TrapdoorStandard.h"
#include "TrapdoorHell.h"

std::unique_ptr<Trapdoor> TrapdoorFactory::createTrapdoor(const string &type, ShaderManager *shaderManager) {
    if (type == "standard") {
        return  std::make_unique<TrapdoorStandard>(shaderManager);
    }
    if (type == "hell") {
        return std::make_unique<TrapdoorHell>(shaderManager);
    }
    throw LemmingsException("Unknown trap door type.");
}
