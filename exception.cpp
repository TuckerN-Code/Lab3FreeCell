/*************************************************************
* Author:         Tucker Nulty
* Filename:       exception.cpp
* Date Created:   3/30/21
* Modifications:
**************************************************************/

#include "exception.h"

Exception::Exception(const char* strIn):
	m_expMessage(strIn)
{
	
}

Exception::Exception(const Exception& copy):
	m_expMessage(copy.m_expMessage)
{
}

Exception::Exception(Exception&& move) noexcept:
	m_expMessage(move.m_expMessage)
{
	move.m_expMessage = nullptr;
}
/**********************************************************************
* Purpose: returns m_expMessage as a const char*
*
* Precondition:
*      m_expMessage must exist
*
* Postcondition:
*      returns m_expMessage
*
************************************************************************/
const char* Exception::getMessage()
{
	return m_expMessage;
}
