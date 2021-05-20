#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"

class Results : public GameState {

public:
    Results(Game *game) : GameState(game) {}

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

private:
    void initButtons();

    void renderButtons();

    Texture backgroundTexture;
    std::unique_ptr<Sprite> background;

    PurplePercentageDisplay currentPercentageDisplay;
    PurplePercentageDisplay goalPercentageDisplay;

    std::unique_ptr<Sprite> continueButton;
    std::unique_ptr<Sprite> retryButton;
    std::unique_ptr<Sprite> menuButton;

    int selectedButton;
    bool passedLevel;

    vector<ResultsButtonName> possibleButtons;

};

#endif // _RESULTS_INCLUDE


