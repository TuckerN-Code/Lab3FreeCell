#include "FreeCells.h"

FreeCells::FreeCells()
{
}

FreeCells::FreeCells(const FreeCells& cpy)
{
	for (int i = 0; i < 4; i++)
	{
		m_cardArray[i] = cpy.m_cardArray[i];
	}
}

FreeCells::FreeCells(FreeCells&& mv) noexcept
{
	for (int i = 0; i < 4; i++)
	{
		m_cardArray[i] = mv.m_cardArray[i];
		mv.m_cardArray[i] = Card();
	}
}

FreeCells::~FreeCells()
{

}

FreeCells FreeCells::operator=(const FreeCells& cpy)
{
	for (int i = 0; i < 4; i++)
	{
		m_cardArray[i] = cpy.m_cardArray[i];
	}
	return *this;
}

void FreeCells::placeCard(Card crd, int pos)
{
	if (pos > 3 || pos < 0)
		throw OutOfBoundsException();
	else if (m_cardArray[pos].getSuite() == 0 && m_cardArray[pos].getValue() == 0)
		m_cardArray[pos] = crd;
	else
		throw Exception("Spot already filled");
		
}

Card FreeCells::removeCard(int pos)
{
	if (pos > 3 || pos < 0)
		throw OutOfBoundsException();
	else if (m_cardArray[pos].getSuite() != 0 && m_cardArray[pos].getValue() != 0)
	{
		Card tempCard = m_cardArray[pos];
		m_cardArray[pos] = Card();
		return tempCard;
	}
		
	else
		throw Exception("Spot already empty");
}

void FreeCells::printFreeCells()
{
	std::cout << "Free Cells:";
	const char cards[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K' };

	for (int i = 0; i < 4; i++)
	{
		std::cout << m_cardArray[i];
	}
	std::cout << std::endl;
}
