/*************************************************************
* Author:         Tucker Nulty
* Filename:       ArrayStack.h
* Date Created:   4/22/21
* Modifications:  4/26/21 -Added elements()
**************************************************************/

#include "Array.h"

#pragma once

/************************************************************************
* Class: LLStack
*
* Purpose: Creates a Stack Array
*
*
* Manager functions:
*       ArrayStack()
*       ArrayStack(const ArrayStack & cpy)
*       ArrayStack(ArrayStack && mv)
*       operator=(const ArrayStack & cpy)
*       ~ArrayStack()
*
* Methods:
*       push(T value)
*			pushes value onto a new node at the head of the list
*		pop()
*			pops the top node from the list and returns the stored data
*		peek()
*			returns the data from the top node in the list
*		size()
*			returns the size of the array
*		elements()
*			returns the amount of data stored
*		isEmpty()
*			checks if the array is empty
*		isFull()
*			checks if the array is full
*		setSize()
*			resizes the array
*************************************************************************/
template<class T>
class ArrayStack
{
public:
	ArrayStack(int size);
	ArrayStack(const ArrayStack& cpy);
	ArrayStack(ArrayStack&& mv) noexcept;
	~ArrayStack();
	ArrayStack operator= (const ArrayStack& cpy);

	void push(T value);
	T pop();
	T peek();
	int size();
	int elements();
	bool isEmpty();
	bool isFull();
	void setSize(int size);
private:
	Array<T> m_internalArray;
	int m_size = 0;
	int m_count = 0;
};

template<class T>
inline ArrayStack<T>::ArrayStack(int size) :
	m_size(size), m_internalArray(Array<T>(size))
{
}

template<class T>
inline ArrayStack<T>::ArrayStack(const ArrayStack& cpy):
	m_internalArray(cpy.m_internalArray), m_size(cpy.m_size)
{
	
}

template<class T>
inline ArrayStack<T>::ArrayStack(ArrayStack&& mv) noexcept :
	m_internalArray(mv.m_internalArray), m_size(mv.m_size)
{
	mv.m_internalArray = nullptr;
	mv.m_size = 0;
}

template<class T>
inline ArrayStack<T>::~ArrayStack()
{
	
}

template<class T>
inline ArrayStack<T> ArrayStack<T>::operator=(const ArrayStack& cpy)
{
	m_internalArray = cpy.m_internalArray;
	m_size = cpy.m_size;
	return *this;
}

/**********************************************************************
* Purpose: pushes the passed data to a new node at the start of the list
*
* Precondition:
*     Node must exist
*
* Postcondition:
*      adds 1 to count and adds the new node to the list
*
************************************************************************/

template<class T>
inline void ArrayStack<T>::push(T value)
{
	if (!isFull())
	{
		Array<T> tmpArray(m_size);
		for (int i = 0; i < m_size; i++)
		{
			tmpArray[i] = m_internalArray[i];
		}
		for (int i = 0; i < m_size-1; i++)
		{
			m_internalArray[i + 1] = tmpArray[i];
		}
		m_internalArray[0] = value;
		m_count++;
	}
	else
	{
		throw OutOfBoundsException();
	}
}

/**********************************************************************
* Purpose: returns the data from the first node in the list and removes the node
*
* Precondition:
*     Node must exist
*
* Postcondition:
*      removes 1 from count and removes the first node from the list
*
************************************************************************/

template<class T>
inline T ArrayStack<T>::pop()
{
	if (!isEmpty())
	{
		T retVal = m_internalArray[0];
		Array<T> tempArray(m_size);
		for (int i = 0; i < m_size; i++)
		{
			tempArray[i] = m_internalArray[i];
		}

		for (int i = 0; i < m_size - 1; i++)
		{
			m_internalArray[i] = tempArray[i+1];
		}

		m_count--;
		return retVal;
	}
	else
	{
		throw OutOfBoundsException();
	}
}

/**********************************************************************
* Purpose: returns the data from the first node in the list
*
* Precondition:
*     Node must exist
*
* Postcondition:
*      returns the data from the first node in the list
*
************************************************************************/

template<class T>
inline T ArrayStack<T>::peek()
{
	return m_internalArray[0];
}

/**********************************************************************
* Purpose: returns m_size
*
* Precondition:
*     m_size must exist
*
* Postcondition:
*      returns m_size
*
************************************************************************/

template<class T>
inline int ArrayStack<T>::size()
{
	return m_size;
}

/**********************************************************************
* Purpose: returns m_count
*
* Precondition:
*     m_count must exist
*
* Postcondition:
*      returns m_count
*
************************************************************************/

template<class T>
inline int ArrayStack<T>::elements()
{
	return m_count;
}

/**********************************************************************
* Purpose: returns if the array is empty or not
*
* Precondition:
*     m_count must exist
*
* Postcondition:
*      returns true if the list is empty
*
************************************************************************/

template<class T>
inline bool ArrayStack<T>::isEmpty()
{
	if (m_count == 0)
		return true;
	else
		return false;
	
}

/**********************************************************************
* Purpose: returns if the array is full or not
*
* Precondition:
*     m_count must exist
*
* Postcondition:
*      returns true if the list is full
*
************************************************************************/

template<class T>
inline bool ArrayStack<T>::isFull()
{
	if (m_count == m_size)
		return true;
	else
		return false;
}

/**********************************************************************
* Purpose: resizes the array
*
* Precondition:
*    m_internalArray must exist
*
* Postcondition:
*      sets m_internalArray to the new size
*
************************************************************************/

template<class T>
inline void ArrayStack<T>::setSize(int size)
{
	Array<T> tempArray(size);
	if (size >= m_size)
	{
		for (int i = 0; i < m_size; i++)
		{
			tempArray[i] = m_internalArray[i];
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			tempArray[i] = m_internalArray[i];
		}
	}
	m_internalArray.setLength(size);
	for (int i = 0; i < size; i++)
	{
		m_internalArray[i] = tempArray[i];
	}
	m_size = size;
}
