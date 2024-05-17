
// (c) 2024 R.Hasaranga

#pragma once

#include "WSHat.h"

#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <malloc.h>
#include "../ViewID.h"

#define BUTTON_DELAY 400
#define MENU_ITEM_TOP 40
#define MENU_ITEM_TEXT_X_GAP 35
#define MENU_ITEM_Y_GAP 45

#define MENU_RECT_COLOR 0xe71c
#define MENU_TEXT_NORMAL_COLOR 0xe71c
#define MENU_TEXT_HIGHLIGHT_COLOR 0x0

class NView
{
protected:
	WSHat* hat;
	Adafruit_GFX_Buffer<Adafruit_ST7789>* tft;
	bool stopFlag;
public:
	NView() {}

	virtual void init(WSHat* hat)
	{
		this->hat = hat;
		tft = hat->getDisplay();
	}

	virtual void start(bool resetLastItemIndex)
	{
		stopFlag = false;
		tft->setFont(&FreeSans12pt7b);
	}

	virtual void loop(bool ignoreKeys)
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::KEY_1))
			stopFlag = true;
	}

	virtual bool shouldStop() { return stopFlag; }
	virtual void stop() {}
	virtual uint8_t getNextViewID() { return MAINMENU_VIEW_ID; }
	virtual bool showLastMenuItem() { return true; }

	~NView() {}
};

class GameListView : public NView
{
private:
	uint8_t currentGameIndex;
	uint8_t nextViewID;

	void reduceGameIndex()
	{
		if (currentGameIndex != 0)
			--currentGameIndex;
	}

	void increaseGameIndex()
	{
		if (currentGameIndex != (GAME_COUNT - 1))
			++currentGameIndex;
	}

	void showGameList(uint8_t selectIndex)
	{
		const char* gameList[] = GAME_LIST;

		tft->fillScreen(ST77XX_BLACK);

		uint8_t yPos = MENU_ITEM_TOP;
		for (int i = 0; i < GAME_COUNT; ++i)
		{
			if (i == selectIndex) {
				tft->setTextColor(MENU_TEXT_HIGHLIGHT_COLOR);
				tft->fillRect(MENU_ITEM_TEXT_X_GAP - 15, yPos - 22, 180, 30, MENU_RECT_COLOR);
			}
			else {
				tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
			}

			tft->setCursor(MENU_ITEM_TEXT_X_GAP, yPos);
			tft->print(gameList[i]);
			yPos += MENU_ITEM_Y_GAP;
		}

		tft->display();
	}
public:
	void init(WSHat* hat) override
	{
		NView::init(hat);
		currentGameIndex = 0;
	}

	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		if (resetLastItemIndex)
			currentGameIndex = 0;

		nextViewID = MAINMENU_VIEW_ID;
		showGameList(currentGameIndex);
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::UP_KEY))
		{
			reduceGameIndex();
			showGameList(currentGameIndex);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{
			increaseGameIndex();
			showGameList(currentGameIndex);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::CENTER_KEY))
		{
			stopFlag = true;
			if(currentGameIndex == 0)
				nextViewID = TIC_TAC_GAME_VIEW;
			else if (currentGameIndex == 1)
				nextViewID = SOKOBAN_GAME_VIEW;
			else if (currentGameIndex == 2)
				nextViewID = WATERSORT_GAME_VIEW;
		}
		else
		{
			NView::loop(ignoreKeys);
		}
	}
	uint8_t getNextViewID() override { return nextViewID; }
};

class SettingsView : public NView
{
private:
	uint8_t backlight;
	uint8_t currentItem;
	const uint8_t itemCount = 1;
	bool shouldCommit;

	void showSettings(uint8_t selectIndex)
	{
		const char* items[] = { "Backlight"};

		char backLightStr[34];
		itoa(backlight, backLightStr, 10);

		const char* itemValues[] = { backLightStr };

		tft->fillScreen(ST77XX_BLACK);

		uint8_t yPos = MENU_ITEM_TOP;
		for (int i = 0; i < itemCount; ++i)
		{
			if (i == selectIndex) {
				tft->setTextColor(MENU_TEXT_HIGHLIGHT_COLOR);
				tft->fillRect(MENU_ITEM_TEXT_X_GAP - 15, yPos - 22, 200, 30, MENU_RECT_COLOR);
			}
			else {
				tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
			}

			tft->setCursor(MENU_ITEM_TEXT_X_GAP, yPos);
			tft->print(items[i]);
			tft->setCursor(MENU_ITEM_TEXT_X_GAP + 130, yPos);
			tft->print(itemValues[i]);
			yPos += MENU_ITEM_Y_GAP;
		}

		tft->display();
	}

	void reduceBacklight()
	{
		if (backlight == SettingsStore::MIN_BACKLIGHT)
			return;

		backlight -= 5;
		hat->setBackLight(backlight);
		SettingsStore::setBacklightLevel(backlight);
		shouldCommit = true;
	}

	void increaseBacklight()
	{
		if (backlight == SettingsStore::MAX_BACKLIGHT)
			return;

		backlight += 5;
		hat->setBackLight(backlight);
		SettingsStore::setBacklightLevel(backlight);
		shouldCommit = true;
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		backlight = SettingsStore::readBacklightLevel();

		shouldCommit = false;
		currentItem = 0;
		showSettings(currentItem);
	}

	void stop() override
	{
		if(shouldCommit)
			SettingsStore::commit();
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::LEFT_KEY))
		{
			if (currentItem == 0) // backlight
			{
				reduceBacklight();
				showSettings(currentItem);
			}
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::RIGHT_KEY))
		{
			if (currentItem == 0) // backlight
			{
				increaseBacklight();
				showSettings(currentItem);
			}
			delay(BUTTON_DELAY);
		}
		else
		{
			NView::loop(ignoreKeys);
		}
	}

};

class AboutView : public NView
{
private:
	uint32_t getTotalHeap(void) {
		extern char __StackLimit, __bss_end__;

		return &__StackLimit - &__bss_end__;
	}

	uint32_t getFreeHeap(void) {
		struct mallinfo m = mallinfo();

		return getTotalHeap() - m.uordblks;
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		tft->setFont(&FreeSans9pt7b);
		tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
		tft->fillScreen(ST77XX_BLACK);
		tft->setCursor(20, 40);
		tft->print(F("Napoleon Console v1.0"));
		tft->setCursor(20, 40 + 30);
		tft->setFont(0);
		tft->setTextColor(ST77XX_ORANGE);
		tft->print(F("(c) 2024 R.Hasaranga"));
		tft->setCursor(20, 40 + 30 + 10);
		tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
		tft->print(F("github.com/hasaranga/napoleon"));

		tft->setCursor(20, 40 + 30 + 10 + 15);

		char strHeap[34];
		itoa(getFreeHeap(), strHeap, 10);

		char text[64];
		strcpy(text, "Free Memory: ");
		strcat(text, strHeap);

		tft->print(text);

		tft->display();
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		NView::loop(ignoreKeys);
	}

};

class MainMenuView : public NView
{
private:
	uint8_t currentIndex;
	const uint8_t itemCount = 3;
	uint8_t nextViewID;

	void reduceIndex()
	{
		if (currentIndex != 0)
			--currentIndex;
	}

	void increaseIndex()
	{
		if (currentIndex != (itemCount - 1))
			++currentIndex;
	}

	void showMenu(uint8_t selectIndex)
	{
		const char* items[] = { "Games", "Settings", "About"};

		tft->fillScreen(ST77XX_BLACK);

		uint8_t yPos = MENU_ITEM_TOP;
		for (int i = 0; i < itemCount; ++i)
		{
			if (i == selectIndex) {
				tft->setTextColor(MENU_TEXT_HIGHLIGHT_COLOR);
				tft->fillRect(MENU_ITEM_TEXT_X_GAP - 15, yPos - 22, 180, 30, MENU_RECT_COLOR);
			}
			else {
				tft->setTextColor(MENU_TEXT_NORMAL_COLOR);
			}

			tft->setCursor(MENU_ITEM_TEXT_X_GAP, yPos);
			tft->print(items[i]);
			yPos += MENU_ITEM_Y_GAP;
		}

		tft->display();
	}

public:
	void start(bool resetLastItemIndex) override
	{
		NView::start(resetLastItemIndex);

		if (resetLastItemIndex)
			currentIndex = 0;

		showMenu(currentIndex);
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::UP_KEY))
		{
			reduceIndex();
			showMenu(currentIndex);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{
			increaseIndex();
			showMenu(currentIndex);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::CENTER_KEY))
		{
			stopFlag = true;
			if (currentIndex == 0)
				nextViewID = GAMELIST_VIEW_ID;
			else if (currentIndex == 1)
				nextViewID = SETTINGS_VIEW_ID;
			else if (currentIndex == 2)
				nextViewID = ABOUT_VIEW_ID;
		}
	}

	uint8_t getNextViewID() override { return nextViewID; }
	bool showLastMenuItem() override { return false; }
};

