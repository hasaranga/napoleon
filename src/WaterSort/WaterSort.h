
// (c) 2024 R.Hasaranga

#pragma once

#include <Arduino.h>
#include "../ViewID.h"
#include "../Console/NView.h"
#include "../Console/SettingsStore.h"
#include "Sprites.h"
#include "Levels.h"

#define WATERSORT_BUTTON_DELAY 250

struct UndoStep {
	uint8_t from;
	uint8_t dest;
};

class WaterSortGameView : public NView
{
private:
	bool isOnMenu;

	uint8_t currentMenuItem;
	const uint8_t menuItemCount = 3;

	uint8_t manualLoadLevel;
	uint8_t currentLevel;

	uint8_t bottles[8][4];
	uint8_t bottleCount;
	uint8_t barCountPerBottle;
	uint8_t bottleSelectIndex;
	int fromBottle; // -1 if none
	uint8_t lastCenterClickedBottle;

	static const uint8_t maxUndoSteps = 50;
	UndoStep undoSteps[maxUndoSteps];
	uint8_t undoStepsCount;

	void reduceMenuSelectionIndex()
	{
		if (currentMenuItem != 0)
			--currentMenuItem;
	}

	void increaseMenuSelectionIndex()
	{
		if (currentMenuItem != (menuItemCount - 1))
			++currentMenuItem;
	}

	bool isEmptyBottle(const uint8_t index)
	{
		return (bottles[index][0] == WS_EMPTY);
	}

	bool isBottleHasSpace(const uint8_t index)
	{
		return (bottles[index][barCountPerBottle-1] == WS_EMPTY);
	}

	void transferBottle(const uint8_t fromBottle, const uint8_t destBottle, bool retry = false)
	{
		// not to same bottle
		if (fromBottle != destBottle)
		{
			// has enough space
			if (isBottleHasSpace(destBottle))
			{
				uint8_t fromBottleTopIndex = 0;
				for (uint8_t i= 0; i < barCountPerBottle; ++i)
				{
					if (bottles[fromBottle][i] == WS_EMPTY)
						break;

					fromBottleTopIndex = i;
				}

				if (isEmptyBottle(destBottle))
				{
					bottles[destBottle][0] = bottles[fromBottle][fromBottleTopIndex];
					bottles[fromBottle][fromBottleTopIndex] = WS_EMPTY;

					UndoStep undoStep;
					undoStep.from = fromBottle;
					undoStep.dest = destBottle;
					addToUndo(undoStep);

					// transfer remaining recursively if available
					transferBottle(fromBottle, destBottle, true);

					if(!retry)
						this->fromBottle = -1;
				}
				else
				{
					uint8_t destBottleEmptyTopIndex;
					for (uint8_t i = 0; i < barCountPerBottle; ++i)
					{
						if (bottles[destBottle][i] == WS_EMPTY)
							break;

						destBottleEmptyTopIndex = (i + 1);
					}

					// destBottleEmptyTopIndex will never become 0 because empty bottles will catch earlier if block.
					// check if colours are equal
					if (bottles[destBottle][destBottleEmptyTopIndex - 1] == bottles[fromBottle][fromBottleTopIndex])
					{
						bottles[destBottle][destBottleEmptyTopIndex] = bottles[fromBottle][fromBottleTopIndex];
						bottles[fromBottle][fromBottleTopIndex] = WS_EMPTY;

						UndoStep undoStep;
						undoStep.from = fromBottle;
						undoStep.dest = destBottle;
						addToUndo(undoStep);

						// transfer remaining recursively if available
						transferBottle(fromBottle, destBottle, true);

						if (!retry)
							this->fromBottle = -1;
					}
					else
					{
						if (!retry)
						{
							if (lastCenterClickedBottle == bottleSelectIndex)
								this->fromBottle = lastCenterClickedBottle;

							lastCenterClickedBottle = bottleSelectIndex;
						}
					}
				}		
			}
			else
			{
				if (!retry)
				{
					if (lastCenterClickedBottle == bottleSelectIndex)
						this->fromBottle = lastCenterClickedBottle;

					lastCenterClickedBottle = bottleSelectIndex;
				}
			}
		}
		else
		{
			if (!retry)
			{
				// from bottle equal dest bottle
				this->fromBottle = -1;
			}
		}
	}

	void checkForWin()
	{
		bool allOK = true;
		for (uint8_t bottleIndex = 0; bottleIndex < bottleCount; ++bottleIndex)
		{
			bool bottleOK = true;
			for (uint8_t barIndex = 0; barIndex <(barCountPerBottle-1); ++barIndex)
			{
				if (bottles[bottleIndex][barIndex] != bottles[bottleIndex][barIndex + 1])
				{
					bottleOK = false;
					break;
				}
			}

			if (!bottleOK)
			{
				allOK = false;
				break;
			}
		}

		if (!allOK)
			return;

		// we have a winner

		bool allLevelsFinished = false;

		if (currentLevel == (WATERSORT_LEVEL_COUNT - 1))
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

		SettingsStore::setWaterSortLevel(currentLevel);
		SettingsStore::commit();

		loadLevel(currentLevel, true);
		showGame();
	}

	void showMenu()
	{
		const char* items[] = { "Continue", "New Game", "Load Level"};

		char levelStr[34];
		itoa(manualLoadLevel+1, levelStr, 10);

		tft->fillScreen(ST77XX_BLACK);

		uint8_t yPos = MENU_ITEM_TOP;
		for (int i = 0; i < menuItemCount; ++i)
		{
			if (i == currentMenuItem) {
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

	void loadLevel(const uint8_t level, bool showLevel = true)
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

		// empty all
		for (uint8_t bottleIndex = 0; bottleIndex < 8; ++bottleIndex)
		{
			for (uint8_t barIndex = 0; barIndex < 4; ++barIndex)
			{
				bottles[bottleIndex][barIndex] = WS_EMPTY;
			}
		}

		const uint8_t* watersort_level = watersort_levels[level];
		bottleCount = watersort_level[0];
		barCountPerBottle = watersort_level[1];

		uint8_t dataIndex = 2;
		for (uint8_t bottleIndex = 0; bottleIndex < bottleCount; ++bottleIndex)
		{
			for (uint8_t barIndex = 0; barIndex < barCountPerBottle; ++barIndex)
			{
				bottles[bottleIndex][barIndex] = watersort_level[dataIndex];
				++dataIndex;
			}
		}

		bottleSelectIndex = 0;
		fromBottle = -1;
		lastCenterClickedBottle = 0;
		undoStepsCount = 0;
	}

	// do not pass WS_EMPTY
	const uint16_t* getTile(const uint8_t id, bool isBottom)
	{
		if (id == WS_RED)
			return isBottom ? watersort_red_down : watersort_red;
		else if (id == WS_YELLOW)
			return isBottom ? watersort_yellow_down : watersort_yellow;
		else if (id == WS_ORANGE)
			return isBottom ? watersort_orange_down : watersort_orange;
		else if (id == WS_GREEN)
			return isBottom ? watersort_green_down : watersort_green;
		else if (id == WS_BLUE)
			return isBottom ? watersort_blue_down : watersort_blue;
		else if (id == WS_PURPLE)
			return isBottom ? watersort_purple_down : watersort_purple;
		else
			return isBottom ? watersort_brown_down : watersort_brown;
	}

	void showGame()
	{
		tft->fillScreen(0x2125);

		uint8_t startX;
		uint8_t bottleGap;
		uint8_t bottleY;

		if (bottleCount <= 3)
		{
			startX = 30;
			bottleGap = 40;
			bottleY = 70;
		}
		else if (bottleCount == 4)
		{
			startX = 16;
			bottleGap = 25;
			bottleY = 70;
		}
		else
		{
			// more than 4 bottles
			startX = 16;
			bottleGap = 25;
			bottleY = 10;
		}
	
		for (uint8_t bottleIndex = 0; bottleIndex < bottleCount; ++bottleIndex)
		{
			if (bottleIndex > 3)
				bottleY = 130;

			// draw bottle
			tft->drawRGBBitmap(startX, bottleY, watersort_empty_bottle,
				WS_BOTTLE_IMG_WIDTH, WS_BOTTLE_IMG_HEIGHT);

			// draw bars
			uint8_t barY = bottleY + 78;
			for (uint8_t barIndex = 0; barIndex < barCountPerBottle; ++barIndex)
			{
				const uint8_t colId = bottles[bottleIndex][barIndex];
				if (colId == WS_EMPTY)
					break;

				const uint16_t* img = getTile(colId, barIndex == 0);
				tft->drawRGBBitmap(startX+4, barY, img, WS_BAR_IMG_WIDTH, WS_BAR_IMG_HEIGHT);

				barY -= WS_BAR_IMG_HEIGHT;
			}

			// draw arrow
			if ((int)bottleIndex == fromBottle)
			{
				tft->drawBitmap(startX, bottleY, watersort_arrow,
					WS_ARRAY_IMG_WIDTH, WS_ARRAY_IMG_HEIGHT, ST77XX_WHITE);
			}

			if (bottleIndex == bottleSelectIndex)
			{
				tft->fillRect(startX+4, bottleY + WS_BOTTLE_IMG_HEIGHT + 6, WS_BOTTLE_IMG_WIDTH - 8, 3, ST77XX_WHITE);
			}

			if (bottleIndex == 3)
				startX = 16;
			else
				startX += WS_BOTTLE_IMG_WIDTH + bottleGap;
		}

		tft->display();
	}

	void moveLeftBottleSelect()
	{
		if (bottleSelectIndex == 0)
			return;

		--bottleSelectIndex;
	}

	void moveRightBottleSelect()
	{
		if (bottleSelectIndex == (bottleCount-1))
			return;

		++bottleSelectIndex;
	}

	void moveUpBottleSelect()
	{
		if (bottleCount < 5)
			return;

		if (bottleSelectIndex > 3)
			bottleSelectIndex -= 4;
	}

	void moveDownBottleSelect()
	{
		if (bottleCount < 5)
			return;

		if (bottleSelectIndex < 4)
		{
			const uint8_t lastBottleIndex = (bottleCount - 1);
			if ((bottleSelectIndex + 4) > lastBottleIndex)
				bottleSelectIndex = lastBottleIndex;
			else
				bottleSelectIndex += 4;
		}
	}

	void addToUndo(UndoStep undoStep)
	{
		if (undoStepsCount == maxUndoSteps)
		{
			// remove first item
			for (int i = 0; i < (undoStepsCount - 1); ++i)
			{
				undoSteps[i] = undoSteps[i + 1];
			}
			--undoStepsCount;
		}

		undoSteps[undoStepsCount] = undoStep;
		++undoStepsCount;
	}

	void doUndo()
	{
		if (undoStepsCount == 0)
			return;

		UndoStep undoStep = undoSteps[undoStepsCount - 1];

		uint8_t fromBottleTopIndex = 0;
		for (uint8_t i = 0; i < barCountPerBottle; ++i)
		{
			if (bottles[undoStep.dest][i] == WS_EMPTY)
				break;

			fromBottleTopIndex = i;
		}

		uint8_t destBottleEmptyTopIndex;
		for (uint8_t i = 0; i < barCountPerBottle; ++i)
		{
			if (bottles[undoStep.from][i] == WS_EMPTY)
				break;

			destBottleEmptyTopIndex = (i + 1);
		}

		bottles[undoStep.from][destBottleEmptyTopIndex] = bottles[undoStep.dest][fromBottleTopIndex];
		bottles[undoStep.dest][fromBottleTopIndex] = WS_EMPTY;

		--undoStepsCount;
		this->fromBottle = -1;
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		isOnMenu = true;
		currentMenuItem = 0;
		currentLevel = 0;
		undoStepsCount = 0;

		manualLoadLevel = SettingsStore::readWaterSortLevel();
		if (manualLoadLevel >= WATERSORT_LEVEL_COUNT)
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
				reduceMenuSelectionIndex();
				showMenu();
				delay(BUTTON_DELAY);
			}
			else
			{
				moveUpBottleSelect();
				showGame();
				delay(WATERSORT_BUTTON_DELAY);
			}	
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{		
			if (isOnMenu)
			{
				increaseMenuSelectionIndex();
				showMenu();
				delay(BUTTON_DELAY);
			}
			else
			{
				moveDownBottleSelect();
				showGame();
				delay(WATERSORT_BUTTON_DELAY);
			}		
		}
		else if (hat->isKeyPressed(WSHat::LEFT_KEY))
		{
			if (!isOnMenu)
			{
				moveLeftBottleSelect();
				showGame();
				delay(WATERSORT_BUTTON_DELAY);
			}
			else
			{
				if (currentMenuItem == 2) // on load level
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
				moveRightBottleSelect();
				showGame();
				delay(WATERSORT_BUTTON_DELAY);
			}
			else
			{
				if (currentMenuItem == 2) // on load level
				{			
					if ((manualLoadLevel+1) < WATERSORT_LEVEL_COUNT)
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
				if (currentMenuItem == 0) // continue
				{
					currentLevel = SettingsStore::readWaterSortLevel();
					if (currentLevel >= WATERSORT_LEVEL_COUNT)
						currentLevel = 0;
				}
				else if (currentMenuItem == 2) // load level
				{
					currentLevel = manualLoadLevel;
				}
				loadLevel(currentLevel, true);
				showGame();
				delay(BUTTON_DELAY);
			}
			else
			{
				if (fromBottle == -1)
				{
					// "from bottle" is not selected

					if (!isEmptyBottle(bottleSelectIndex))
					{
						fromBottle = bottleSelectIndex;
						lastCenterClickedBottle = bottleSelectIndex;
					}
				}
				else
				{
					// "from bottle" is already selected

					transferBottle(fromBottle, bottleSelectIndex, false);
				}
				showGame();
				checkForWin();
				delay(WATERSORT_BUTTON_DELAY);
			}	
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
				delay(WATERSORT_BUTTON_DELAY);
				return;
			}
			delay(BUTTON_DELAY);
		}
	}

	uint8_t getNextViewID() override { return GAMELIST_VIEW_ID; }
};