#ifndef _RESULTS_INCLUDE
#define _RESULTS_INCLUDE

#include "GameState.h"
#include "Sprite.h"
#include "PurplePercentageDisplay.h"

class Results : public GameState
{

public:
	enum ResultsButtonName {
		RETRY,
		CONTINUE,
		MENU
	};


	static Results &getInstance()
	{
		static Results instance; // Guaranteed to be destroyed.
											   // Instantiated on first use.
		return instance;
	};

	void init();
	void update(int deltaTime);
	void render();
	
	void setPercentages(int goalPercentage, int currentPercentage);

	int getSelectedButtonIndex();
	int getSelectedButton();
	void changeSelectedButtonLeft();
	void changeSelectedButtonRight();

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


