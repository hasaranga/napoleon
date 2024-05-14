
// (c) 2024 R.Hasaranga

#pragma once

#include <Arduino.h>
#include "../ViewID.h"
#include "../Console/NView.h"
#include "Sprites.h"

#define TICTAC_SELECTOR_COL 0xb5b6

class TicTacGameView : public NView
{
private:
	uint8_t currentBox;
	uint8_t boxList[9];
	bool gameFinished;

	const int EMPTY_BOX = 0;
	const int USER_MARKED_BOX = 1;
	const int PC_MARKED_BOX = 2;

	// returns EMPTY_BOX if draw or game can continue
	int getWinner()
	{
		// Possible winning lines
		const int winningLines[8][3] = {
			{0, 1, 2},  // First row
			{3, 4, 5},  // Second row
			{6, 7, 8},  // Third row
			{0, 3, 6},  // First column
			{1, 4, 7},  // Second column
			{2, 5, 8},  // Third column
			{0, 4, 8},  // Diagonal from top-left to bottom-right
			{2, 4, 6}   // Diagonal from top-right to bottom-left
		};

		// Check each winning line for a winner
		for (int i=0; i<8; ++i)
		{
			const int* line = winningLines[i];
			const int boxOwner = boxList[line[0]];

			if (boxOwner == EMPTY_BOX)
				continue;

			if ((boxList[line[1]] == boxOwner) && (boxList[line[2]] == boxOwner))
				return boxOwner;
		}

		return EMPTY_BOX;
	}

	// returns true if we have a winner or draw
	bool checkGameFinished()
	{
		const int winner = getWinner();

		if (winner != EMPTY_BOX)
		{
			// show winner
			gameFinished = true;
			updateScreen(false);

			tft->setTextColor(ST77XX_WHITE);
			
			if (winner == USER_MARKED_BOX)
			{
				tft->setCursor(80, 120);
				tft->print("Win");
			}
			else 
			{
				tft->setCursor(60, 120);
				tft->print("Lose");
			}

			tft->display();
			return true;
		}
		else
		{
			if (hasEmptyBoxes())
				return false;

			// show draw
			gameFinished = true;
			updateScreen(false);

			tft->setTextColor(ST77XX_WHITE);
			tft->setCursor(70, 120);
			tft->print("Draw");
			tft->display();

			return true;
		}
	}

	bool hasEmptyBoxes()
	{
		for (int i = 0; i < 9; ++i)
			if (boxList[i] == EMPTY_BOX)
				return true;
		return false;
	}

	int findWinningMove(int player) {
		int winningLines[8][3] = {
			{0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
			{0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
			{0, 4, 8}, {2, 4, 6}              // Diagonals
		};

		for (int i = 0; i < 8; ++i)
		{
			const int* line = winningLines[i];
			int a = line[0], b = line[1], c = line[2];
			// Find the line with two marks by the same player and an empty spot
			if ((boxList[a] == boxList[b]) && (boxList[c] == EMPTY_BOX) && (boxList[a] == player)) {
				return c;
			}
			if ((boxList[b] == boxList[c]) && (boxList[a] == EMPTY_BOX) && (boxList[b] == player)) {
				return a;
			}
			if ((boxList[a] == boxList[c]) && (boxList[b] == EMPTY_BOX) && (boxList[a] == player)) {
				return b;
			}
		}

		return -1; // No winning move found
	}

	void pcMark()
	{
		int availableMoves[9];
		int availableMovesCount = 0;

		for (int i = 0; i < 9; ++i)
		{
			if (boxList[i] == EMPTY_BOX)
			{
				availableMoves[availableMovesCount] = i;
				++availableMovesCount;
			}
		}

		int nextMove;
		if (availableMovesCount == 1) 
		{
			nextMove = availableMoves[0];
		}
		else
		{
			nextMove = findWinningMove(PC_MARKED_BOX);
			if (nextMove == -1)
			{
				// blocking movement behaviour is random
				//if ((random(0, 2) == 0))
				if(true)
				{
					// block move
					nextMove = findWinningMove(USER_MARKED_BOX);
					if (nextMove == -1)
					{
						// random move
						nextMove = availableMoves[(int)random(0, availableMovesCount)];
					}
				}
				else
				{
					nextMove = availableMoves[(int)random(0, availableMovesCount)];
				}
			}
		}

		boxList[nextMove] = PC_MARKED_BOX;

		updateScreen(true);
	}

	void resetGame()
	{
		gameFinished = false;
		currentBox = 0;
		for (int i = 0; i < 9; ++i)
			boxList[i] = EMPTY_BOX;
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
		updateScreen(true);
	}

	void updateScreen(bool sendData)
	{
		tft->drawRGBBitmap(0, 0, tictac_background, 240, 240);

		for (int i = 0; i < 9; ++i)
		{
			if(boxList[i] == USER_MARKED_BOX)
				tft->drawBitmap(79 * (i % 3), 79 * (i / 3), tictac_user_mark, 82, 83, ST77XX_BLACK);
			else if (boxList[i] == PC_MARKED_BOX)
				tft->drawBitmap(79 * (i % 3), 79 * (i / 3), tictac_pc_mark, 82, 83, ST77XX_BLACK);
		}

		if(!gameFinished)
			tft->drawBitmap(79 * (currentBox % 3), 79 * (currentBox / 3), tictac_select, 82, 83, TICTAC_SELECTOR_COL);

		if(sendData)
			tft->display();
	}

	void loop(bool ignoreKeys) override
	{
		if (ignoreKeys)
			return;

		if (hat->isKeyPressed(WSHat::UP_KEY))
		{
			if (gameFinished)
				return;

			if ((currentBox / 3) == 0)
				return;

			currentBox -= 3;
			updateScreen(true);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::DOWN_KEY))
		{
			if (gameFinished)
				return;

			if ((currentBox / 3) == 2)
				return;

			currentBox += 3;
			updateScreen(true);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::RIGHT_KEY))
		{
			if (gameFinished)
				return;

			if ((currentBox % 3) == 2)
				return;

			++currentBox;
			updateScreen(true);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::LEFT_KEY))
		{
			if (gameFinished)
				return;

			if ((currentBox % 3) == 0)
				return;

			--currentBox;
			updateScreen(true);
			delay(BUTTON_DELAY);
		}
		else if (hat->isKeyPressed(WSHat::CENTER_KEY))
		{
			if (gameFinished) 
			{
				resetGame();
				updateScreen(true);
				delay(BUTTON_DELAY);
				return;
			}
				
			if (boxList[currentBox] != EMPTY_BOX)
				return;

			boxList[currentBox] = USER_MARKED_BOX;
			updateScreen(true);
			delay(700);
			
			if (!checkGameFinished())
			{
				pcMark();
				checkGameFinished();
			}
		}
		else
		{
			NView::loop(ignoreKeys);
		}
	}

	uint8_t getNextViewID() override { return GAMELIST_VIEW_ID; }
};