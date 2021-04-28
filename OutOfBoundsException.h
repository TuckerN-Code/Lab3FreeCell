#include "exception.h"
#pragma once
class OutOfBoundsException : Exception
{
public:
	OutOfBoundsException() : Exception("Out of Bounds")
	{
		
	}
};

