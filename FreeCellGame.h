#pragma once
#include "FreeCells.h"
#include "HomeCells.h"
#include "TableStack.h"

class FreeCellGame
{
public:
	FreeCellGame();
	FreeCellGame(const FreeCellGame& cpy);
	FreeCellGame(FreeCellGame&& mv) noexcept;
	~FreeCellGame();
	FreeCellGame operator=(const FreeCellGame& cpy);

	void runGame();
	void endGame();
	void refreshBoard();
	void takeTurn();

private:
	void invalidOption(const char* msg);
	void placeHome(int pos, Card crd);
	void placeTable(int pos, Card crd);
	void placeFree(int pos, Card crd);
	int pickUpCardTable();
	int pickUpCardFree();
	int chooseCardDest();
	void badPlaceInputTable(int pos, Card crd);
	void badPlaceInputFree(int pos, Card crd);

	FreeCells m_gameFreeCells;
	HomeCells m_gameHomeCells;
	TableStack m_gameTableStack;
	Card m_gameCurrentCard;
	bool m_quit = false;
};

