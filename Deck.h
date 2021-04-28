
#include "card.h"
#include <iostream>
#include <ctime>

#pragma once
class Deck
{
public:
	Deck();
	Deck(const Deck& cpy);
	Deck(Deck&& mv) noexcept;
	Deck operator=(const Deck& cpy);
	~Deck();

	void shuffle();
	Card getCard(int pos);
	void printDeck();
	Card operator[](int pos);
private:
	Card m_cardDeck[52];
};

