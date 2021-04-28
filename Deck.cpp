#include "Deck.h"

Deck::Deck()
{
	int suite = 1, value = 1;
	for (int i = 0; i < 52; i++)
	{
		m_cardDeck[i].setSuite(suite);
		m_cardDeck[i].setValue(value);
		if (value == 13)
		{
			value = 1;
			suite++;
		}
		else
			value++;
	}

}

Deck::Deck(const Deck& cpy)
{
	for (int i = 0; i < 52; i++)
	{
		m_cardDeck[i] = cpy.m_cardDeck[i];
	}
}

Deck::Deck(Deck&& mv) noexcept
{
	for (int i = 0; i < 52; i++)
	{
		m_cardDeck[i] = mv.m_cardDeck[i];
		mv.m_cardDeck[i].setSuite(0);
		mv.m_cardDeck[i].setValue(0);
	}
}

Deck Deck::operator=(const Deck& cpy)
{
	for (int i = 0; i < 52; i++)
	{
		m_cardDeck[i] = cpy.m_cardDeck[i];
	}
	return *this;
}

Deck::~Deck()
{
}

void Deck::shuffle()
{
	srand((unsigned)time(0));
	Card tempDeck[52];
	for (int i = 0; i < 52; i++)
	{
		
		while (tempDeck[i].getSuite() == 0 && tempDeck[i].getValue() == 0)
		{
			int randpos = rand() % 52;
			if (m_cardDeck[randpos].getSuite() != 0 && m_cardDeck[randpos].getSuite() != 0)
			{
				tempDeck[i] = m_cardDeck[randpos];
				m_cardDeck[randpos] = Card(0, 0);
			}
		}
	}

	for (int i = 0; i < 52; i++)
	{
		m_cardDeck[i] = tempDeck[i];
	}
}

Card Deck::getCard(int pos)
{
	return m_cardDeck[pos];
}

void Deck::printDeck()
{
	for (int i = 0; i < 52; i++)
	{
		std::cout << i << " " << m_cardDeck[i].getSuite() << " " << m_cardDeck[i].getValue() << std::endl;
	}
}

Card Deck::operator[](int pos)
{
	if (pos < 0 || pos > 52)
	{
		throw OutOfBoundsException();
	}
	return m_cardDeck[pos];
}
