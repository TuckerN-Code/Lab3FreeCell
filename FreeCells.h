#include "Card.h"
#include "OutOfBoundsException.h"

#pragma once
class FreeCells
{
public:
	FreeCells();
	FreeCells(const FreeCells& cpy);
	FreeCells(FreeCells&& mv) noexcept;
	~FreeCells();
	FreeCells operator=(const FreeCells & cpy);

	void placeCard(Card crd,int pos);
	Card removeCard(int pos);
	void printFreeCells();

private:
	Card m_cardArray[4];
};

