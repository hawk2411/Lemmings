#ifndef _NUMDISPLAYGREEN_INCLUDE
#define _NUMDISPLAYGREEN_INCLUDE

#include "NumDisplay.h"

class NumDisplayGreen : public NumDisplay {
public:
    void setPosition(glm::vec2 position) override;

private:
    void initAux(ShaderManager *shaderManager) override;

    void displayNumAux(int firstDigit, int secondDigit) override;

};

#endif // _NUMDISPLAYGREEN_INCLUDE


