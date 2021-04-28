#include "Card.h"
#include "ArrayStack.h"

#pragma once
class HomeCells
{
public:
	HomeCells();
	HomeCells(const HomeCells& cpy);
	HomeCells(HomeCells&& mv) noexcept;
	~HomeCells();
	HomeCells operator=(const HomeCells& cpy);

	bool placeCard(Card crd);
	Card popCard(int suite);
	void printHomeCells();
	bool checkWin();

private:
	ArrayStack<Card> m_homeArrays[4]{ 13, 13, 13, 13 };

};

