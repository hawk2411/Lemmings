#ifndef _UI_INCLUDE
#define _UI_INCLUDE

#include "Button.h"
#include "Texture.h"
#include "Sprite.h"
#include "Job.h"
#include "NumDisplayGreen.h"
#include "PercentageDisplay.h"
#include "TimeDisplay.h"


class UI
{

public:
	static UI &getInstance()
	{
		static UI instance; // Guaranteed to be destroyed.
							   // Instantiated on first use.
		return instance;
	};

	void init();
	void update();
	void render();
	void setPosition(glm::vec2 position);

	int getButtonIndexInPos(int posX, int posY);
	void changeSelectedButton(int selectedButton);
	int getSelectedButtonJobCount();

	void changeDisplayedJob(string lemmingJobName);

private:
	static const int NUM_BUTTONS = 13;

	glm::vec2 position;

	Button buttons[NUM_BUTTONS];

	Texture backgroundTexture;
    std::unique_ptr<Sprite> background;

    std::unique_ptr<Sprite> jobName;

    std::unique_ptr<Sprite> outWord;
	NumDisplayGreen numberOutLemmings;

    std::unique_ptr<Sprite> inWord;
	PercentageDisplay numberInLemmings;

    std::unique_ptr<Sprite> timeWord;
	TimeDisplay time;
	


	int selectedButton;
	Texture selectFrameTexture;
	std::unique_ptr<Sprite> selectFrame;
};

#endif // _UI_INCLUDE


