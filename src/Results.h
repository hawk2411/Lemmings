#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"

class Results : public GameState {

public:
    enum ResultsButtonName {
        RETRY,
        CONTINUE,
        MENU
    };


    static Results &getInstance() {
        static Results instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };

    void init() override;

    void update(int deltaTime) override;

    void render() override;

    void setPercentages(int goalPercentage, int currentPercentage);

    int getSelectedButtonIndex() const;

    int getSelectedButton();

    void changeSelectedButtonLeft();

    void changeSelectedButtonRight();

    void keyPressed(int key) override;

    void keyReleased(int key) override;

    void specialKeyPressed(int key) override;

    void specialKeyReleased(int key) override;

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


