#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	// Change aesthetic appearance of our Snake, so basically the body is gonna have a 3
	// different colors they're just different shades of green, so 3 shades of green and 
	// it's gonna go dark, medium, light, medium, dark again repeating in that pattern.
	// We can create an array with our colors in it and then we can cycle throught those
	// colors throughtout the whole body when we initialize the Snake for the first time.
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = 
	{
		// Array of Colors.
		{10, 100, 32},	// Low
		{10, 130, 48},	// Medium
		{18, 160, 48},	// High
		{10, 130, 48}	// Medium
	};
	// Loop throught all the segments in the array and we're gonna initalize the body color
	// of each of those segments to one of the colors inside of this array.
	for (int i = 0; i < nSegmentsMax; ++i)
	{
		// Normaly we're indexing throught all the segments and we're giving them a color from
		// array of colors and the index "i" is the same as the index from the segment but aray 
		// of Colors has only 4 elements and our segment array is gonna have probably like a 100
		// so very quickly your index is gonna go past the end of array of colors and that's not a 
		// good scene you never want to index past the end of your array, what this does this is 
		// the modulus "%" and this gives you the remainder of a division.
		// We can use modulus to constrain these indexes to between 0 and 3 and always looping thorught
		// those values even thought the index is gonna be higher and higher up to 100 or up to 99.
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}

	// Set up the Head.
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	// We got to start at the tail and make our way to the Head.
	// "nSegments - 1" -> is the last segment in the Snake that's currently being used.
	// "i > 0" -> because we don't want to process the Head the Head will be moved by
	// delta location so we only wanna process all of the segments up to but not
	// including the Head.
	// "--i" -> we'll be decrementing until we reach the Head and we'll stop and not 
	// process the Head.
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	// This should move our entire Snake based on delta location.
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	// "segments.[0]" -> is the Head.
	// This is gonna return a copy of the location of that segment it's gonna return
	// a new location object and then we're gonna call on that object.
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	// Increase number of segments being used the size of the array that's
	// being used. 
	// Let's make it safe and let's check to see if "nSegments" is less than 
	// "nSegmentsMax" and we only increase it if it's smaller than the max.
	if (nSegments < nSegmentsMax)
	{
		// "nSegments" points at the next free segment the next unused segment
		// in the array so what we want to do is first we want to go segments 
		// and then we want to go at "nSegments" and so on in the next unused 
		// segment we want to initialize it as a body segment and then we want 
		// to increment the "nSegments" to indicate that the number of used segments
		// has increased.
		++nSegments;
	}
}

void Snake::Draw(Board & brd) const
{
	// Loop thorugh all the segments and for each of those segments we're just call
	// Draw on that segment.
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTile(const Location & target) const
{
	// For every active segment of the Snake what we're gonna do is we're
	// gonna check to see if that segments location is equal to the target 
	// location.
	for (int i = 0; i < nSegments; ++i)
	{
		
		// If they are equal then we want to return true because the Snkae is in
		// the target tile.
		if (segments[i - 1].GetLocation() == target)
		{
			return true;
		}
	}

	// Otherwise if it runs through all the segments and hasn't found any that are
	// equal.
	return false;
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	// For every active segment of the Snake what we're gonna do is we're
	// gonna check to see if that segments location is equal to the target 
	// location.
	// "nSegments - 1" -> this is going to check all of the segments except for 
	// the very end.
	for (int i = 0; i < nSegments - 1; ++i)
	{

		// If they are equal then we want to return true because the Snkae is in
		// the target tile.
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	// Otherwise if it runs through all the segments and hasn't found any that are
	// equal.
	return false;
}

//Location Snake::Segment::GetLocation() const
//{
//	return loc;
//}

// It's gonna return a constant reference to the Location of the segment.
const Location& Snake::Segment::GetLocation() const
{
	// It's gonna return a constant reference to the Location of the segment.
	return loc;
}


void Snake::Segment::InitHead(const Location & in_loc)
{
	// Assigning data members from Init Location to Segment Location.
	loc = in_loc;

	// Head Color is actually a private member but we're accessing it from a different
	// class and you might say well why can you do that well the reason is because
	// Segment Class is inside of a Snake Class so just like when functions are inside
	// of a class they can access the private data members, if classes are inside
	// of another class they cna also access the private data members of that class.
	// This can be good or it can be bad depending on your situation, but just be 
	// aware that's a thing that can happen and it can sometimes break encapsualtion
	// if you don't use it properly.
	c = Snake::HeadColor;
}

//void Snake::Segment::InitBody()
//{
//	// Set the Snake Body Color.
//	c = Snake::BodyColor;
//}

void Snake::Segment::InitBody(Color c_in)
{
	// Initialize the Snake Body Color.
	c = c_in;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	// We're gonna check to make sure that the delta is a valid delta, assert that the
	// absolute value of "delta_loc.x" + "delta_loc.y" is exactly equal to 1, and the
	// way this works is because the only valid delta has to have "x" or "y" that only
	// one of them can be either 1 or -1, so the absolute value "abs" it takes an value
	// ad if it's negative it turns a negative into a positive. 
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);

	// This is a tricky one actually, basically what MoveBy is gonna do is it's gonna 
	// add the delta value to our location of our segment.
	// The thing about MoveBy is we only want to be able to move a Snake by one square,
	// one square either horizontally or vertically. 
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}
