#pragma once
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <exception>
#include <stdexcept>

/*****************************************************************
 This is an implementation of a Gap Buffer. A data structure that stores and manages a string.

 This data structure keeps a cursor somewhere along the string, and with it, it is able to insert in O(n), amortized cost, 
 where n is the size of the inserted string at the position of the cursor.
 
 This data structure is very fast at making many consecutive insertions at the same position.
******************************************************************/
class GapBuffer {
	// Char arrays containing the characters before and after of the cursor
	char *front, *back;
	// Capacity of the front and back arrays
	size_t cap;
	// Sizes of the strings stored at the front and back of the cursor
	size_t size1, size2;

	
	//Resizes the gap buffer. The size must be at least as big as the size of the string stored.
	void resize(const size_t& new_capacity) 
	{
		if(new_capacity < size1+size2)
			throw std::invalid_argument("The new size is invalid.");

		// Copies the front of the string
		char* aux = new char[new_capacity];
		std::strncpy(aux, front, size1);
		delete[] front;
		front = aux;

		// Copies the back of the string
		aux = new char[new_capacity];
		std::strncpy(aux+new_capacity-size1, back+cap-size1, size2);
		delete[] back;
		back = aux;

		// Updates the capacity
		cap = new_capacity;
	}
public:
	
	/**
	Initialization of the gap buffer. The default capacity is 20 characters.
	@param capacity of the buffer
	*/
	GapBuffer(const size_t& capacity = 20) : 
		front(new char[capacity]), 
		back(new char[capacity]), 
		cap(capacity), 
		size1(0), 
		size2(0) {}

	/**
	Initializes the gab buffer with the given std::string.
	@param string
	*/
	GapBuffer(std::string str) :
		front(new char[str.size()]),
		back(new char[str.size()]),
		cap(str.size()),
		size1(str.size()),
		size2(0)
	{
		std::copy(str.begin(), str.end(), front);
	}
	
	/**
	Returns the size of the stored string.
	@return size of the string
	*/
	inline size_t size() const 
	{ 
		return size1 + size2; 
	}
	
	/**
	Inserts a string at the cursor and moves the cursor forward 'size' positions.
	@param str char array
	@param size size of the array to insert
	*/
	void insert(const char* str, const size_t& size) 
	{
		// If the arrays need to be expanded
		if (size1 + size2 + size > cap)
			resize(cap * 2);

		// Insertion of the string
		strncpy(front + size1, str, size);
		size1 += size;
	}

	/**
	Inserts a string at the cursor.
	@param str char array
	@param size size of the array to insert
	*/
	void stable_insert(const char* str, const size_t& size)
	{
		size2 += size;

		// If the arrays need to be expanded
		if (size1 + size2 > cap)
			resize(cap * 2);

		// Insertion of the string
		strncpy(back + cap - size2, str, size);
	}
	
	/**
	Inserts a character at the cursor.
	@param c character to insert
	*/
	void insert(const char& c) 
	{
		// If the arrays need to be expanded
		if (size1 + size2 >= cap)
			resize(cap * 2);

		// Insertion of the character
		front[size1] = c;
		size1 += 1;
	}

	/**
	Erases n positions in front of the cursor. There must be num removable characters in front of the cusor.
	@param num number of characters to erase
	*/
	void erase(const size_t num) 
	{
		// If there are not enough characters to erase
		if (size2 < num)
			throw std::invalid_argument("The size exceeds the removable space.");
		
		// If the size of the string is sufficiently smaller than the capacity to resize the gap buffer
		if (size1 + size2 < cap / 4)
			resize(cap / 2);

		// Erase the characters
		size2 -= num;
	}
	
	/**
	Moves the cursor to the given position. The position must be inside the size of the string.
	*/
	void move_cursor(const size_t pos)
	{
		// If the position is outside the string
		if(pos < 0 || pos > size1 + size2)
			throw std::invalid_argument("The position is outside the string.");

		// Displacement of the position
		int disp = pos - size1;
		if (disp > 0)  //The displacement is forward
		{
			strncpy(front + size1, back + cap - size2, (size_t) disp);
			size1 = pos;
			size2 -= disp;
		}
		else if(disp < 0) // The displacement is backwards
		{
			strncpy(back + cap - size2 + disp, front + size1 + disp, (size_t) -disp);
			size1 += disp;
			size2 -= disp;
		}

	}
	/** 
	Returns the string stored as a std::string object.
	@return returns the almacenated string
	*/
	std::string get_string() const
	{
		std::string str(front,size1);
		str.append(back + cap - size2, size2);
		return str;
	}
};