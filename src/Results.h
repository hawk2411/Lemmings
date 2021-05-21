#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"

class Results : public GameState {

public:
    Results(Game *game, LevelModes::Mode levelMode, int level) : GameState(game), _levelMode(levelMode), _level(level) {}

    enum ResultsButtonName {
        RETRY,
        CONTINUE,
        MENU
    };

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void setPercentages(int goalPercentage, int currentPercentage);

    int getSelectedButtonIndex() const;

    int getSelectedButton();

    void changeSelectedButtonLeft();

    void changeSelectedButtonRight();

    void onKeyPressed(const SDL_KeyboardEvent &keyboardEvent) override;

    void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton) override;

    void setLevel(LevelModes::Mode mode, int level){ _levelMode= mode; _level = level;}

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

    LevelModes::Mode _levelMode;
    int _level;

};

#endif // _RESULTS_INCLUDE


