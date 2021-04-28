#include "OutOfBoundsException.h"

#pragma once

enum value
{
	J = 11,
	Q = 12,
	K = 13,
	A = 1,
};

class Card
{
public:
	Card();
	Card(const Card& cpy);
	Card(Card&& mv) noexcept;
	Card operator=(const Card& cdIn);
	~Card();
	Card(int suite, int value);
	int getSuite();
	int getValue();
	void setSuite(int suite);
	void setValue(int value);

	friend std::ostream& operator<<(std::ostream& os, const Card& crd)
	{
		const char cards[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K' };
		if (crd.m_suite != 0)
			os << '|' << crd.m_suite << " " << cards[crd.m_value-1] << "| ";
		else
			os << "|- -| ";
		return os;
	}
private:
	int m_suite;
	int m_value;
};

