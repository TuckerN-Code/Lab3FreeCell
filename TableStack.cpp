#include "TableStack.h"

TableStack::TableStack()
{
	m_playingDeck.shuffle();
	int j = 0;
	for (int i = 0; i < 52; i++)
	{
		if (m_tableArray[j].elements() == 7)
		{
			j++;
		}
		else if (i > 28 && m_tableArray[j].elements() == 6)
		{
			j++;
		}
		m_tableArray[j].push(m_playingDeck[i]);
	}
}

TableStack::TableStack(const TableStack& cpy)
{
	for (int i = 0; i < 8; i++)
	{
		m_tableArray[i] = cpy.m_tableArray[i];
	}
	m_playingDeck = cpy.m_playingDeck;
}

TableStack::TableStack(TableStack&& mv) noexcept
{
	for (int i = 0; i < 8; i++)
	{
		m_tableArray[i] = mv.m_tableArray[i];
		for (int j = 0; j < 13; j++)
		{
			mv.m_tableArray[i].pop();
		}
	}
	m_playingDeck = mv.m_playingDeck;
	mv.m_playingDeck = Deck();
}

TableStack::~TableStack()
{
}

TableStack TableStack::operator=(const TableStack& cpy)
{
	for (int i = 0; i < 8; i++)
	{
			m_tableArray[i] = cpy.m_tableArray[i];
	}
	m_playingDeck = cpy.m_playingDeck;
	return *this;
}

bool TableStack::placeCard(Card crd,int pos)
{
	int suite1 = 0, suite2 = 0;

	switch (crd.getSuite())
	{
	case 1:
		suite1 = 2;
		suite2 = 4;
		break;
	case 2:
		suite1 = 1;
		suite2 = 3;
		break;
	case 3:
		suite1 = 2;
		suite2 = 4;
		break;
	case 4:
		suite1 = 1;
		suite2 = 3;
		break;
	}

	if (pos < 0 || pos > 8)
	{
		throw OutOfBoundsException();
	}
	else
	{
		if (m_tableArray[pos].peek().getValue() == crd.getValue() + 1
			|| m_tableArray[pos].peek().getSuite() == suite1
			|| m_tableArray[pos].peek().getSuite() == suite2)
		{
			m_tableArray[pos].push(crd);
			return true;
		}
		else if (m_tableArray[pos].isEmpty())
		{
			m_tableArray[pos].push(crd);
			return true;
		}
		return false;
	}

}

void TableStack::undoPopCard(Card crd, int pos)
{
	if (pos < 0 || pos > 8)
	{
		throw OutOfBoundsException();
	}
	else
	{
		m_tableArray[pos].push(crd);
	}
}

Card TableStack::popCard(int pos)
{
	if (pos < 0 || pos > 8)
	{
		throw OutOfBoundsException();
	}
	else
	{
		return m_tableArray[pos].pop();
	}
	
}

void TableStack::printTable()
{
	std::cout << "Tables:    \n";
	ArrayStack<Card> tmpArray[8]{ 13,13,13,13,13,13,13,13 };
	int k = 0;
	const char cards[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K' };
	for (int j = 0; j < 13; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_tableArray[i].elements() > 0)
				tmpArray[i].push(m_tableArray[i].pop());
		}
	}

	k = 0;
	for (int j = 0; j < 13; j++)
	{
		std::cout << "           ";
		for (int i = 0; i < 8; i++)
		{
			
			if (!tmpArray[i].isEmpty())
			{
				std::cout << tmpArray[i].peek();
				m_tableArray[i].push(tmpArray[i].pop());
				k++;
				if (i == 7)
				{
					std::cout << std::endl;
				}
			}
			else if (!tmpArray[0].isEmpty() || !tmpArray[1].isEmpty()
				|| !tmpArray[2].isEmpty() || !tmpArray[3].isEmpty()
				|| !tmpArray[4].isEmpty() || !tmpArray[5].isEmpty()
				|| !tmpArray[6].isEmpty() || !tmpArray[7].isEmpty())
			{

				std::cout << tmpArray[i].peek();
				if (i == 7)
				{
					std::cout << std::endl;
				}
			}	
		}
	}
	std::cout << std::endl;

}
