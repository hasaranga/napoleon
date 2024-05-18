
// (c) 2024 R.Hasaranga

#pragma once

#include <Arduino.h>
#include "../ViewID.h"
#include "../Console/NView.h"
#include "Sprites.h"

#define NUMSLIDE_BUTTON_DELAY 250

class NumberSlideGameView : public NView
{
private:
	uint8_t emptyBoxIndex;
	uint8_t boxList[9];
	bool gameFinished;

	const uint8_t BOX_1 = 1;
	const uint8_t BOX_2 = 2;
	const uint8_t BOX_3 = 3;
	const uint8_t BOX_4 = 4;
	const uint8_t BOX_5 = 5;
	const uint8_t BOX_6 = 6;
	const uint8_t BOX_7 = 7;
	const uint8_t BOX_8 = 8;
	const uint8_t EMPTY_BOX = 0;

	void shuffleBoxes() {
		// Fisher-Yates Shuffle Algorithm
		for (int i = 8; i > 0; i--) {
			uint8_t j = (uint8_t)random(0, (i + 1));
			uint8_t temp = boxList[i];
			boxList[i] = boxList[j];
			boxList[j] = temp;
		}
	}

	bool isSolvable()
	{
		int inversions = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = i + 1; j < 9; j++) {
				if ((boxList[i] != EMPTY_BOX) && (boxList[j] != EMPTY_BOX) && (boxList[i] > boxList[j])) {
					inversions++;
				}
			}
		}
		return inversions % 2 == 0;
	}

	void resetGame()
	{
		for (int i = 0; i < 9; i++)
		{
			boxList[i] = i;
		}

		do {
			shuffleBoxes();
		} while (!isSolvable());
		
		// find the empty box location
		for (int i = 0; i < 9; i++)
		{
			if (boxList[i] == EMPTY_BOX)
			{
				emptyBoxIndex = i;
				break;
			}		
		}
		
		gameFinished = false;	
	}

	void checkForWin()
	{
		bool win = true;
		for (int i = 0; i < 8; i++)
		{
			if (boxList[i] != (i+1))
			{
				win = false;
				break;
			}
		}

		if (win)
		{
			delay(600);
			gameFinished = true;
			tft->setTextColor(ST77XX_WHITE);
			tft->setCursor(80, 120);
			tft->print("Win");
			tft->display();
		}
	}

	const uint16_t* getTile(uint8_t id)
	{
		if (id == BOX_1)
			return numberslide_1;
		else if (id == BOX_2)
			return numberslide_2;
		else if (id == BOX_3)
			return numberslide_3;
		else if (id == BOX_4)
			return numberslide_4;
		else if (id == BOX_5)
			return numberslide_5;
		else if (id == BOX_6)
			return numberslide_6;
		else if (id == BOX_7)
			return numberslide_7;
		else if (id == BOX_8)
			return numberslide_8;
		else
			return numberslide_empty;
	}

	void updateScreen()
	{
		for (int i = 0; i < 9; i++)
		{
			const uint16_t* image = getTile(boxList[i]);
			tft->drawRGBBitmap(80 * (i % 3), 80 * (i / 3), image, 80, 80);
		}

		tft->display();
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		randomSeed(millis());
		resetGame();

		tft->setFont(&FreeSansBold24pt7b);
		tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
		tft->setCursor(0, 0);
		updateScreen();
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::UP_KEY))
		{
			if (gameFinished)
				return;

			if ((emptyBoxIndex / 3) == 2)
				return;

			const uint8_t fromBox = emptyBoxIndex + 3;
			boxList[emptyBoxIndex] = boxList[fromBox];
			boxList[fromBox] = EMPTY_BOX;
			emptyBoxIndex = fromBox;

			updateScreen();
			checkForWin();

			delay(NUMSLIDE_BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{
			if (gameFinished)
				return;

			if ((emptyBoxIndex / 3) == 0)
				return;

			const uint8_t fromBox = emptyBoxIndex - 3;
			boxList[emptyBoxIndex] = boxList[fromBox];
			boxList[fromBox] = EMPTY_BOX;
			emptyBoxIndex = fromBox;

			updateScreen();
			checkForWin();
				
			delay(NUMSLIDE_BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::RIGHT_KEY))
		{
			if (gameFinished)
				return;

			if ((emptyBoxIndex % 3) == 0)
				return;

			const uint8_t fromBox = emptyBoxIndex - 1;
			boxList[emptyBoxIndex] = boxList[fromBox];
			boxList[fromBox] = EMPTY_BOX;
			emptyBoxIndex = fromBox;

			updateScreen();
			checkForWin();

			delay(NUMSLIDE_BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::LEFT_KEY))
		{
			if (gameFinished)
				return;

			if ((emptyBoxIndex % 3) == 2)
				return;

			const uint8_t fromBox = emptyBoxIndex + 1;
			boxList[emptyBoxIndex] = boxList[fromBox];
			boxList[fromBox] = EMPTY_BOX;
			emptyBoxIndex = fromBox;

			updateScreen();
			checkForWin();

			delay(NUMSLIDE_BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::CENTER_KEY))
		{
			if (gameFinished) 
			{
				resetGame();
				updateScreen();
			}
			delay(BUTTON_DELAY);
		}
		else
		{
			NView::loop(ignoreKeys);
		}
	}

	uint8_t getNextViewID() override { return GAMELIST_VIEW_ID; }
};