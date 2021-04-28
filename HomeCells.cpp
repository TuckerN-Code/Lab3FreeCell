#include "HomeCells.h"

HomeCells::HomeCells()
{
}

HomeCells::HomeCells(const HomeCells& cpy)
{
	for (int i = 0; i < 4; i++)
	{
		m_homeArrays[i] = cpy.m_homeArrays[i];
	}
}

HomeCells::HomeCells(HomeCells&& mv) noexcept
{
	for (int i = 0; i < 4; i++)
	{
		m_homeArrays[i] = mv.m_homeArrays[i];
		for (int j = 0; j < 13; j++)
		{
			mv.m_homeArrays[j].pop();
		}
	}
}

HomeCells::~HomeCells()
{
}

HomeCells HomeCells::operator=(const HomeCells& cpy)
{
	for (int i = 0; i < 4; i++)
	{
		m_homeArrays[i] = cpy.m_homeArrays[i];
	}
	return *this;
}

bool HomeCells::placeCard(Card crd)
{
	if (crd.getValue() == m_homeArrays[crd.getSuite()-1].peek().getValue() - 1)
	{
		m_homeArrays[crd.getSuite()-1].push(crd);
		return true;
	}
	else if (crd.getValue() == A)
	{
		m_homeArrays[crd.getSuite()-1].push(crd);
		return true;
	}
	return false;
}

Card HomeCells::popCard(int suite)
{
	if (suite > 4 || suite < 1)
		throw OutOfBoundsException();
	else
		return m_homeArrays[suite-1].pop();
}

void HomeCells::printHomeCells()
{
	std::cout << "Home Cells:";
	const char cards[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K' };

	for (int i = 0; i < 4; i++)
	{
		std::cout << m_homeArrays[i].peek();
	}
	std::cout << std::endl;
}

bool HomeCells::checkWin()
{
	if (m_homeArrays[1].peek().getValue() == K && m_homeArrays[2].peek().getValue() == K && m_homeArrays[0].peek().getValue() == K && m_homeArrays[3].peek().getValue() == K)
		return true;
	else
		return false;
}


