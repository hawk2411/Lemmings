#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "ShaderManager.h"
#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"
#include "LevelIndex.h"

class Results : public GameState {

public:
    Results(Game *game, const LevelIndex& levelIndex);

    enum ResultsButtonName {
        RETRY,
        CONTINUE,
        MENU
    };

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void setPercentages(int goalPercentage, int currentPercentage);

    int getSelectedButton();

    void changeSelectedButtonLeft();

    void changeSelectedButtonRight();

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void changeLevel(const LevelIndex& levelIndex);

private:
    void initButtons();

    void renderButtons();

    vector<ResultsButtonName> possibleButtons;

    Texture backgroundTexture;
    std::unique_ptr<Sprite> background;

    PurplePercentageDisplay currentPercentageDisplay;
    PurplePercentageDisplay goalPercentageDisplay;

    std::unique_ptr<Sprite> continueButton;
    std::unique_ptr<Sprite> retryButton;
    std::unique_ptr<Sprite> menuButton;

    int selectedButton{};
    bool passedLevel{};

    LevelIndex _levelIndex;
    ShaderManager* _shaderManager;

};

#endif // _RESULTS_INCLUDE


