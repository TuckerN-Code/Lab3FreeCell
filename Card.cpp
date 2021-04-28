#include "Card.h"

Card::Card()
{
	m_suite = 0;
	m_value = 0;
}

Card::Card(const Card& cpy) :
	m_suite(cpy.m_suite), m_value(cpy.m_value)
{

}

Card::Card(Card&& mv) noexcept:
	m_suite(mv.m_suite), m_value(mv.m_value)
{
	mv.m_suite = 0;
	mv.m_value = 0;
}

Card Card::operator=(const Card& cdIn)
{
	m_suite = cdIn.m_suite;
	m_value = cdIn.m_value;
	return *this;
}

Card::~Card()
{
}

Card::Card(int suite, int value) :
	m_suite(suite), m_value(value)
{
}

int Card::getSuite()
{
	return m_suite;
}

int Card::getValue()
{
	return m_value;
}

void Card::setSuite(int suite)
{
	m_suite = suite;
}

void Card::setValue(int value)
{
	m_value = value;
}

