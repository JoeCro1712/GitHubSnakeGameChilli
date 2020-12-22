#pragma once

#include "Board.h"

// The Snake is gonna be modeled with two classes we're going to have one class
// that represents the Snake as a whole entity and we're have another class that
// represents a segment of the Snake so the Snake class is gonna have an array of
// segment objects and it's gonna manage them and it's gonna be the Snake class that
// ties all the segment together and the Snake class is what the other entities
// in the game are gonna interact with and the Snake class is gonna manage all the
// segments that are inside the Snake.

// There's someting in the C++ language that can let us do, we can declare a class
// inside of another class. This give's us some advantages because the outside world
// doesen't actually have to know about Snake Segments that's an implementation detail
// that's internal to Snake, this inner class and we make it private then the outside 
// world doesen't have to know anything about how a Snake implemented segments it's
// only concerned with the interface of the Snake itself.

class Snake
{
private:
	class Segment
	{
	public:
		// Functions to initialize segment when the Snake grows.
		// InitHead takes a Location because we have to specify the location of the
		// head when the Snkae is created and InitBody doesen't take that because 
		// the Body is just going to follow the segment before it so it doesen't matter
		// what you set it to as soon as you move the Snake it is going to move to the
		// proper position.
		void InitHead(const Location& in_loc);
		/*void InitBody();*/
		void InitBody(Color c_in);

		// The way that Snake moving works isn't complicated, what you're going to do
		// is you're gonna gave each segment follow the next segment starting from the
		// tail and working towards the head so for a delta_loc(0, 1) so starting from 
		// the tail follow the next one until you reach the head and then you just move 
		// in the delta location, note that this wouldn't work if you try it the other 
		// way if you start with the head. 
		void Follow(const Segment& next);

		// This function will move a segment by a certain amount.
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;

		// Free the location of the segments.
		// GetLocation() is returning a copy of Location but smoetimes we don't want to 
		// copy that we just want to reference it.
		//Location GetLocation() const;
		
		// Make it return it const reference to the Location because we don't always want
		// to make a copy, sometimes we just want to look at it.
		const Location& GetLocation() const;
	private:
		// Location of the Segment.
		Location loc;

		// Give each Segment Color.
		Color c;
	};
public:
	// Constructor to make a Snake and we should be able to specify where the Snake
	// starts off on the grid with the Location.
	Snake(const Location& loc);

	// Function MoveBy which moves the Snake by a certain delta value what a delta value
	// means is for example it's getting passed a Location and let's say that delta Location
	// is equal delta_loc(1, 0) so that means moving 1 in the positive x direciton.
	void MoveBy(const Location& delta_loc);

	// Function gives us information on where the Snake is gonna end up next after
	// a delta is applied to it.
	Location GetNextHeadLocation(const Location& delta_loc) const;

	// Function that causes the Snake to grow and we'll call this one whenever it eats one
	// of the fruit.
	void Grow();

	// Function to draw the Snake to the Board.
	void Draw(Board& brd) const;

	// Function for Colliding Snake itself.
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;
private:
	// Colors of the Snake, the Head and the Body color.
	static constexpr Color HeadColor = Colors::Yellow;
	static constexpr Color BodyColor = Colors::Green;

	// Maximum number of elements, the actuall size of array.
	static constexpr int nSegmentsMax = 100;

	// Array of Segments.
	Segment segments[nSegmentsMax];

	// How many segments are currently existing or how many elements of array are
	// we currently using.
	int nSegments = 1;
};