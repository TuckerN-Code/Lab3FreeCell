/*************************************************************
* Author:         Tucker Nulty 
* Filename:       Array.h
* Date Created:   3/30/21 
* Modifications:  4/14/21 – refactored pointerarray code into a dynamic array
**************************************************************/
#pragma once

#include "OutOfBoundsException.h"


template <class T>

/************************************************************************ 
* Class: Array 
* 
* Purpose: Creates and stores a pointer array  
* 
* Manager functions:   
*       Array (int size) 
*               Creates a pointer to a pointer array with size 'size'        
*       Array (const Array & p1) 
*       Array (const Array && p1)
*       operator = (const Array & copy) 
*       ~Array() 
* 
* Methods:              
*       operator [ ] (int index) 
*		operator= (T& val) 
*			Used to set the value of the position the array is at to 'val'
*		operator= (T&& val)
*			Used to set the value of the position the array is at to 'val'
*		operator[](int pos)
*			Returns the pointer of the array at the position passed
*		operator==(T val)
*			Checks if the value passed is equal to the value the array is on
*		at(int pos)
*           Returns the pointer of the array at the position passed
*		size()
*			Returns the m_size value
*		data()
*			Returns the m_Array pointer
*		for_each(void(*f)(T))
*			Iterates through all values in the array and pssing them to the passed function
*		push_back(T value)
*			Pushes the value given value to the end of the array and increases the array size
*		pop_back()
*			Removes the last value in the array and makes the array smaller
*		setLength(int size)
*			Changes the size of the array
*		getStartIndex()
*			returns the start index
*		setStartIndex(int val)
*			sets the start index
*************************************************************************/
class Array
{
private:
	int m_pos;
	int m_size;
	T *m_Array;
	

public:
	Array(int size);
	Array(const Array& p1);
	Array(Array&& p1) noexcept;
	~Array();

	T* data();
	T& at(int pos);
	int size();
	void for_each(void (*f)(T));

	void push_back(T value);
	void pop_back();
	void setLength(int size);

	int getStartIndex();
	void setStartIndex(int val);



	struct iterator 
	{
		using iterator_catagoty = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;

		iterator(T* ptr) : m_ptr(ptr) {}

		iterator operator= (const iterator& copy) { m_ptr = copy.m_ptr; }
		iterator operator= (iterator&& mv) { m_ptr = mv.m_ptr; mv.m_ptr = nullptr; }

		T& operator* () const { return *m_ptr; }
		
		iterator& operator++() { m_ptr++; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

		iterator begin() { return iterator(&m_Array[0]); }
		iterator end() { return iterator & m_Array[m_size]; }


	private:
		T* m_ptr;
	};

	Array operator= (const Array& copy)
	{

		m_size = copy.m_size;
		m_pos = copy.m_pos;
		m_Array = copy.m_Array;
		return *this;
	}
	Array operator= (T& val)
	{

		*m_Array[m_pos] = val;

		return *this;
	}

	Array operator= (T&& val)
	{
		*m_Array[m_pos] = val;

		return *this;
	}

	T& operator[](int pos)
	{
		if ((pos < 0 || pos >= m_size) && m_pos >= 0)
		{
			throw Exception("Position out of array");
		}
		else if ((pos < m_pos || pos >= abs(m_pos + m_size)) && m_pos < 0)
		{
			throw Exception("Position out of array");
		}
		if (pos < 0)
		{
			return m_Array[m_size + pos];
		}
		else
			return m_Array[pos-m_pos];

	}

	Array operator==(T val)
	{
		bool checkSame;

		if (*m_Array[m_pos] == *val)
			checkSame = true;
		else
			checkSame = false;
		return checkSame;
	}	
	
	Array operator!=(T val)
	{
		bool checkSame;

		if (*m_Array[m_pos] != *val)
			checkSame = true;
		else
			checkSame = false;
		return checkSame;
	}



};

template<class T>
inline Array<T>::Array(int size) :
	m_size(size), m_pos(0)
{
	if (size < 0)
	{
		throw Exception("Array Invalid Size");
	}
	m_Array = new T[size];
}

template<class T>
inline Array<T>::Array(const Array& p1):
	m_size(p1.m_size), m_pos(p1.m_pos), m_Array(p1.m_Array)
{

}

template<class T>
inline Array<T>::Array(Array&& p1) noexcept:
	m_size(p1.m_size), m_pos(p1.m_pos), m_Array(p1.m_Array)
{
	p1.m_size = 0;
	p1.m_pos = 0;
	p1.m_Array = nullptr;
}

template<class T>
inline Array<T>::~Array()
{
	delete[] m_Array;
}

/**********************************************************************
* Purpose: This function uses the input int to navigate to that
*		position in the array and return the pointer stored
*
* Precondition:
*     pos must be any int with in the size limit of m_Array
*
* Postcondition:
*      returns the pointer stored at the position of pos
*
************************************************************************/

template<class T>
T& Array<T>::at(int pos)
{
	if (pos < 0 || pos >= m_size)
	{
		throw OutOfBoundsException();
	}
	return m_Array[pos];
}

/**********************************************************************
* Purpose: Returns the size of the array
*
* Precondition:
*     Array must exist
*
* Postcondition:
*      returns private variable m_size
*
************************************************************************/


template<class T>
int Array<T>::size()
{
	return m_size;
}

/**********************************************************************
* Purpose: Returns the raw array
*
* Precondition:
*     array must exist
*
* Postcondition:
*      returns the raw pointer array
*
************************************************************************/

template<class T>
T* Array<T>::data()
{
	return m_Array;
}
/**********************************************************************
* Purpose: Takes in a function and runs it on all values stored in the array
*
* Precondition:
*     Array must exist
*
* Postcondition:
*      Runs the function taken on all data values in the array
*
************************************************************************/

template<class T>
inline void Array<T>::for_each(void(*f)(T))
{
	for (int i = 0; i < m_size; i++)
	{
		f(at(i));
	}
}

/**********************************************************************
* Purpose: takes in a value and pushes it to the end of the array
*
* Precondition:
*     Array must exist
*
* Postcondition:
*      array size increases by 1 and last value set equal to taken in value
*
************************************************************************/

template<class T>
inline void Array<T>::push_back(T value)
{
	Array temp(m_size);
	for (int i = 0; i < m_size; i++)
	{
		temp[i] = m_Array[i];
	}
	delete m_Array;
	m_Array = new T[m_size + 1];
	m_size++;
	for (int i = 0; i < m_size - 1; i++)
	{
		m_Array[i] = temp[i];
	}
	m_Array[m_size - 1] = value;
}

/**********************************************************************
* Purpose: pops out the last value in the array
*
* Precondition:
*     Array must exist
*
* Postcondition:
*      array size decreases by 1
*
************************************************************************/

template<class T>
inline void Array<T>::pop_back()
{
	Array temp(m_size);
	for (int i = 0; i < m_size; i++)
	{
		temp[i] = m_Array[i];
	}
	delete m_Array;
	m_Array = new T[m_size - 1];
	for (int i = 0; i < m_size - 1; i++)
	{
		m_Array[i] = temp[i];
	}
	m_size--;
}

/**********************************************************************
* Purpose: takes in an int and sets the array to that size
*
* Precondition:
*     Array must exist
*
* Postcondition:
*      array size becomes equal to passed size
*
************************************************************************/

template<class T>
inline void Array<T>::setLength(int size)
{
	if (size < 0)
	{
		throw Exception("Array Invalid Size");
	}
	Array temp(m_size);
	for (int i = 0; i < m_size; i++)
	{
		temp[i] = m_Array[i];
	}
	delete m_Array;
	m_Array = new T[size];
	for (int i = 0; i < m_size; i++)
	{
		if (i < size)
			m_Array[i] = temp[i];
	}
	m_size = size;
}

/**********************************************************************
* Purpose: returns the start index
*
* Precondition:
*     m_pos must be set
*
* Postcondition:
*      returns m_pos
*
************************************************************************/

template<class T>
inline int Array<T>::getStartIndex()
{
	return m_pos;
}
/**********************************************************************
* Purpose: takes in an int and sets it as the start of the array index
*
* Precondition:
*     m_pos must exist
*
* Postcondition:
*      m_pos is set to the passed int
*
************************************************************************/
template<class T>
inline void Array<T>::setStartIndex(int val)
{
	m_pos = val;
}


