/*************************************************************
* Author:         Tucker Nulty
* Filename:       exception.h
* Date Created:   3/30/21
* Modifications:
**************************************************************/
#include <iostream>

#pragma once
 class Exception
{
public:
	Exception(const char* strIn);
	Exception(const Exception& copy);
	Exception(Exception&& move) noexcept;
	const char* getMessage();
private:
	const char* m_expMessage;


};

