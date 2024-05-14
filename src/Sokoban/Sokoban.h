
// (c) 2024 R.Hasaranga

#pragma once

#include <Arduino.h>
#include "../ViewID.h"
#include "../Console/NView.h"
#include "../Console/SettingsStore.h"
#include "Sprites.h"
#include "Levels.h"

#define SOKOBAN_BUTTON_DELAY 250

#define SK_UNDO_UP 1
#define SK_UNDO_DOWN 2
#define SK_UNDO_LEFT 3
#define SK_UNDO_RIGHT 4
#define SK_UNDO_UP_BOX 5
#define SK_UNDO_DOWN_BOX 6
#define SK_UNDO_LEFT_BOX 7
#define SK_UNDO_RIGHT_BOX 8

class SokobanGameView : public NView
{
private:
	bool isOnMenu;

	uint8_t currentItem;
	const uint8_t itemCount = 3;

	uint8_t gameScreen[64];
	uint8_t playerPos;
	uint8_t currentLevel;
	const uint8_t* defaultLayout;
	uint8_t pointBoxCount;

	static const uint8_t maxUndoSteps = 50;
	uint8_t undoSteps[maxUndoSteps];
	uint8_t undoStepsCount;

	uint8_t manualLoadLevel;

	void reduceSelectionIndex()
	{
		if (currentItem != 0)
			--currentItem;
	}

	void increaseSelectionIndex()
	{
		if (currentItem != (itemCount - 1))
			++currentItem;
	}

	void showMenu()
	{
		const char* items[] = { "Continue", "New Game", "Load Level"};

		char levelStr[34];
		itoa(manualLoadLevel+1, levelStr, 10);

		tft->fillScreen(ST77XX_BLACK);

		uint8_t yPos = MENU_ITEM_TOP;
		for (int i = 0; i < itemCount; ++i)
		{
			if (i == currentItem) {
				tft->setTextColor(MENU_TEXT_HIGHLIGHT_COLOR);
				tft->fillRect(MENU_ITEM_TEXT_X_GAP - 15, yPos - 22, 200, 30, MENU_RECT_COLOR);
			}
			else {
				tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
			}

			tft->setCursor(MENU_ITEM_TEXT_X_GAP, yPos);
			tft->print(items[i]);
			if (i == 2) {
				tft->setCursor(MENU_ITEM_TEXT_X_GAP + 130, yPos);
				tft->print(levelStr);
			}
			yPos += MENU_ITEM_Y_GAP;
		}

		tft->display();
	}

	void loadLevel(uint8_t level, bool showLevel = true)
	{
		if (showLevel)
		{
			// show level number
			tft->fillScreen(ST77XX_BLACK);
			tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
			tft->setCursor(75, 120);

			char strLevel[34];
			itoa(level+1, strLevel, 10);

			char text[64];
			strcpy(text, "Level ");
			strcat(text, strLevel);

			tft->print(text);
			tft->display();

			delay(800);
		}

		// load level
		defaultLayout = sokoban_levels[level];
		memcpy(gameScreen, defaultLayout, 64);

		pointBoxCount = 0;
		for (int i = 0; i < 64; ++i)
		{
			if (gameScreen[i] == SK_PL)
			{
				playerPos = i;
			}
			else if( (gameScreen[i] == SK_PB) || (gameScreen[i] == SK_YB))
			{
				++pointBoxCount;
			}
		}

		undoStepsCount = 0;
	}

	const uint16_t* getTile(uint8_t id)
	{
		if (id == SK_GB)
			return sokoban_greybrick;
		else if (id == SK_EB)
			return sokoban_emptybox;
		else if (id == SK_PB)
			return sokoban_pointbox;
		else if (id == SK_YB)
			return sokoban_yellowbox;
		else if (id == SK_RB)
			return sokoban_redbox;
		else
			return sokoban_player;		
	}

	void showGame()
	{
		for (int i = 0; i < 64; ++i)
		{
			const uint16_t* image = getTile(gameScreen[i]);
			tft->drawRGBBitmap((i%8)*30, (i/8)*30, image, 30, 30);
		}

		tft->display();
	}

	void checkForWin()
	{
		uint8_t yellowBoxCount = 0;
		for (int i = 0; i < 64; ++i)
		{
			if (gameScreen[i] == SK_YB)
			{
				++yellowBoxCount;
			}
		}

		if (pointBoxCount == yellowBoxCount)
		{
			bool allLevelsFinished = false;

			if (currentLevel == (SKOBAN_LEVEL_COUNT - 1))
			{
				allLevelsFinished = true;
			}
			else
			{
				++currentLevel;
			}

			delay(800); // wait some time to see last movement

			if (allLevelsFinished) // all levels clear and back to beginning
			{
				tft->fillScreen(ST77XX_BLACK);
				tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
				tft->setCursor(75, 120);

				tft->print("All Clear");
				tft->display();

				delay(800);

				isOnMenu = true;
				showMenu();

				return;
			}

			SettingsStore::setSokobanLevel(currentLevel);
			SettingsStore::commit();

			loadLevel(currentLevel, true);
			showGame();
		}
	}

	// returns 0 on no change. 1 on movement. 2 on box movement
	uint8_t changePlayerPosition(const uint8_t nextPos, const int afterNextPos)
	{
		// next is greybrick
		if (gameScreen[nextPos] == SK_GB)
			return 0;

		// next is emptybox or pointbox
		if ((gameScreen[nextPos] == SK_EB) || (gameScreen[nextPos] == SK_PB))
		{
			gameScreen[nextPos] = SK_PL;
			if ((defaultLayout[playerPos] == SK_PB) || (defaultLayout[playerPos] == SK_YB))
				gameScreen[playerPos] = SK_PB;
			else
				gameScreen[playerPos] = SK_EB;

			playerPos = nextPos;
			return 1;
		}

		// next is redbox or yellowbox
		if ((gameScreen[nextPos] == SK_RB) || (gameScreen[nextPos] == SK_YB))
		{
			if (afterNextPos == -1)
				return 0;

			// after next is emptybox or pointbox
			if ((gameScreen[afterNextPos] == SK_EB) || (gameScreen[afterNextPos] == SK_PB))
			{
				if (gameScreen[afterNextPos] == SK_PB)
					gameScreen[afterNextPos] = SK_YB;
				else
					gameScreen[afterNextPos] = SK_RB;

				gameScreen[nextPos] = SK_PL;

				if( (defaultLayout[playerPos] == SK_PB) || (defaultLayout[playerPos] == SK_YB))
					gameScreen[playerPos] = SK_PB;
				else
					gameScreen[playerPos] = SK_EB;

				playerPos = nextPos;
				return 2;
			}
		}

		return 0;
	}

	void addToUndo(uint8_t step)
	{
		if (undoStepsCount == maxUndoSteps)
		{
			// remove first item
			for (int i = 0; i < (undoStepsCount - 1); ++i)
			{
				undoSteps[i] = undoSteps[i+1];
			}
			--undoStepsCount;
		}

		undoSteps[undoStepsCount] = step;
		++undoStepsCount;
	}

	void moveLeftPlayer()
	{
		const uint8_t currentXPos = (playerPos % 8);

		if (currentXPos == 0)
			return;

		const uint8_t nextPos = playerPos - 1;
		const int afterNextPos = ((nextPos % 8) == 0) ? -1 : (nextPos - 1);

		const uint8_t movement = changePlayerPosition(nextPos, afterNextPos);

		if (movement != 0)
			addToUndo( (movement == 2) ? SK_UNDO_LEFT_BOX : SK_UNDO_LEFT);
	}

	void moveRightPlayer()
	{
		const uint8_t currentXPos = (playerPos % 8);

		if (currentXPos == 7)
			return;

		const uint8_t nextPos = playerPos + 1;
		const int afterNextPos = ((nextPos % 8) == 7) ? -1 : (nextPos + 1);

		const uint8_t movement = changePlayerPosition(nextPos, afterNextPos);

		if (movement != 0)
			addToUndo((movement == 2) ? SK_UNDO_RIGHT_BOX : SK_UNDO_RIGHT);
	}

	void moveUpPlayer()
	{
		const uint8_t currentYPos = (playerPos / 8);

		if (currentYPos == 0)
			return;

		const uint8_t nextPos = playerPos - 8;
		const int afterNextPos = ((nextPos / 8) == 0) ? -1 : (nextPos - 8);

		const uint8_t movement = changePlayerPosition(nextPos, afterNextPos);

		if (movement != 0)
			addToUndo((movement == 2) ? SK_UNDO_UP_BOX : SK_UNDO_UP);
	}

	void moveDownPlayer()
	{
		const uint8_t currentYPos = (playerPos / 8);

		if (currentYPos == 7)
			return;

		const uint8_t nextPos = playerPos + 8;
		const int afterNextPos = ((nextPos / 8) == 7) ? -1 : (nextPos + 8);

		const uint8_t movement = changePlayerPosition(nextPos, afterNextPos);

		if (movement != 0)
			addToUndo((movement == 2) ? SK_UNDO_DOWN_BOX : SK_UNDO_DOWN);
	}

	void doUndo()
	{
		if (undoStepsCount == 0)
			return;

		const uint8_t movement = undoSteps[undoStepsCount-1];
		
		if ((movement == SK_UNDO_UP) || (movement == SK_UNDO_DOWN) || 
			(movement == SK_UNDO_LEFT) || (movement == SK_UNDO_RIGHT))
		{
			uint8_t nextPos;
			
			if (movement == SK_UNDO_UP)
				nextPos = playerPos + 8;
			else if(movement == SK_UNDO_DOWN)
				nextPos = playerPos - 8;
			else if (movement == SK_UNDO_LEFT)
				nextPos = playerPos + 1;
			else
				nextPos = playerPos - 1;

			gameScreen[nextPos] = SK_PL;

			if ((defaultLayout[playerPos] == SK_PB) || (defaultLayout[playerPos] == SK_YB))
				gameScreen[playerPos] = SK_PB;
			else
				gameScreen[playerPos] = SK_EB;

			playerPos = nextPos;
			--undoStepsCount;
		}
		else if ((movement == SK_UNDO_UP_BOX) || (movement == SK_UNDO_DOWN_BOX) ||
			(movement == SK_UNDO_LEFT_BOX) || (movement == SK_UNDO_RIGHT_BOX))
		{
			uint8_t nextPos,boxOldPos;

			if (movement == SK_UNDO_UP_BOX)
			{
				nextPos = playerPos + 8;
				boxOldPos = playerPos - 8;
			}
			else if (movement == SK_UNDO_DOWN_BOX)
			{
				nextPos = playerPos - 8;
				boxOldPos = playerPos + 8;
			}
			else if (movement == SK_UNDO_LEFT_BOX)
			{
				nextPos = playerPos + 1;
				boxOldPos = playerPos - 1;
			}
			else
			{
				nextPos = playerPos - 1;
				boxOldPos = playerPos + 1;
			}

			gameScreen[nextPos] = SK_PL;

			if ((defaultLayout[playerPos] == SK_PB) || (defaultLayout[playerPos] == SK_YB))
				gameScreen[playerPos] = SK_YB;
			else
				gameScreen[playerPos] = SK_RB;

			if((defaultLayout[boxOldPos] == SK_PB) || (defaultLayout[boxOldPos] == SK_YB))
				gameScreen[boxOldPos] = SK_PB;
			else
				gameScreen[boxOldPos] = SK_EB;

			playerPos = nextPos;
			--undoStepsCount;
		}
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		isOnMenu = true;
		currentItem = 0;
		currentLevel = 0;
		undoStepsCount = 0;

		manualLoadLevel = SettingsStore::readSokobanLevel();
		if (manualLoadLevel >= SKOBAN_LEVEL_COUNT)
			manualLoadLevel = 0;

		showMenu();
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::UP_KEY))
		{
			if (isOnMenu)
			{
				reduceSelectionIndex();
				showMenu();
				delay(BUTTON_DELAY);
			}
			else
			{
				moveUpPlayer();
				showGame();
				checkForWin();
				delay(SOKOBAN_BUTTON_DELAY);
			}	
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{		
			if (isOnMenu)
			{
				increaseSelectionIndex();
				showMenu();
				delay(BUTTON_DELAY);
			}
			else
			{
				moveDownPlayer();
				showGame();
				checkForWin();
				delay(SOKOBAN_BUTTON_DELAY);
			}		
		}
		else if (hat->isKeyPressed(WSHat::LEFT_KEY))
		{
			if (!isOnMenu)
			{
				moveLeftPlayer();
				showGame();
				checkForWin();
				delay(SOKOBAN_BUTTON_DELAY);
			}
			else
			{
				if (currentItem == 2) // on load level
				{
					if (manualLoadLevel > 0)
						--manualLoadLevel;

					showMenu();
				}
				delay(BUTTON_DELAY);
			}
		}
		else if (hat->isKeyPressed(WSHat::RIGHT_KEY))
		{
			if (!isOnMenu)
			{
				moveRightPlayer();
				showGame();
				checkForWin();
				delay(SOKOBAN_BUTTON_DELAY);
			}
			else
			{
				if (currentItem == 2) // on load level
				{			
					if ((manualLoadLevel+1) < SKOBAN_LEVEL_COUNT)
						++manualLoadLevel;

					showMenu();
				}
				delay(BUTTON_DELAY);
			}		
		}
		else if (hat->isKeyPressed(WSHat::CENTER_KEY))
		{
			if (isOnMenu)
			{
				isOnMenu = false;

				currentLevel = 0; // new game
				if (currentItem == 0) // continue
				{
					currentLevel = SettingsStore::readSokobanLevel();
					if (currentLevel >= SKOBAN_LEVEL_COUNT)
						currentLevel = 0;
				}
				else if (currentItem == 2) // load level
				{
					currentLevel = manualLoadLevel;
				}
				loadLevel(currentLevel, true);
				showGame();
			}
			delay(BUTTON_DELAY);
		}
		else if(hat->isKeyPressed(WSHat::KEY_1))
		{
			if (!isOnMenu)
			{
				isOnMenu = true;
				showMenu();
				delay(BUTTON_DELAY);
			}
			else
			{
				NView::loop(ignoreKeys);
			}
		}
		else if (hat->isKeyPressed(WSHat::KEY_2))
		{
			if (!isOnMenu)
			{
				loadLevel(currentLevel, false);
				showGame();
			}
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::KEY_3))
		{
			if (!isOnMenu)
			{
				doUndo();
				showGame();
				delay(SOKOBAN_BUTTON_DELAY);
				return;
			}
			delay(BUTTON_DELAY);
		}
	}

	uint8_t getNextViewID() override { return GAMELIST_VIEW_ID; }
};