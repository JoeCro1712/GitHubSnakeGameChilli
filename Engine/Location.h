#pragma once
/*
struct Location
{
	// Function that will facilitate adding a delta value to a location.
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	
	int x;
	int y;
};
*/

class Location
{
public:
	// Function that will facilitate adding a delta value to a location.
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	// Define the operator.
	// The left hand side of the comparison is the object on which this function will
	// be called, and the right hand side is passed in as a parameter.
	bool operator == (const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};
