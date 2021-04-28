#include "ArrayStack.h"
#include "Deck.h"
#include <iostream>

#pragma once
class TableStack
{
public:
	TableStack();
	TableStack(const TableStack& cpy);
	TableStack(TableStack&& mv) noexcept;
	~TableStack();
	TableStack operator=(const TableStack& cpy);

	bool placeCard(Card crd, int pos);
	void undoPopCard(Card crd, int pos);
	Card popCard(int pos);
	void printTable();

private:
	ArrayStack<Card> m_tableArray[8]{ 13,13,13,13,13,13,13,13 };
	Deck m_playingDeck;
};

