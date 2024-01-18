#ifndef _NUMDISPLAYBUTTON_INCLUDE
#define _NUMDISPLAYBUTTON_INCLUDE

#include "NumDisplay.h"

class NumDisplayButton : public NumDisplay {
public:
    void setPosition(glm::vec2 position) override;

private:
    void initAux(ShaderManager *shaderManager) override;

    void displayNumAux(int firstDigit, int secondDigit) override;

};

#endif // _NUMDISPLAYBUTTON_INCLUDE


