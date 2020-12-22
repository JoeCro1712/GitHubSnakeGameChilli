#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);

	// Function for randomly generating Position of the Goal.
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);

	// Function Draw the Goal to the Board.
	void Draw(Board& brd) const;

	// We can also get the Location of the Goal which will be useful to test if 
	// the Snake has gonna eat it.
	const Location& GetLocation() const;
private:
	// Define Color.
	static constexpr Color c = Colors::Red;
	// Define a Position of the Goal.
	Location loc;
};