#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	// Creating constructor that initializes the graphics.
	Board(Graphics& gfx);
	// Function to Draw Rectangles to screen.
	// Function is not "const" because it's going to be changing 
	// graphics member Color.
	void DrawCell(const Location& loc, Color c);
	// Get the dimension of the grid.
	int GetGridWidth() const;
	int GetGridHeight() const;

	// Function for Snake Colliding with the Wall.
	// This is going to be a constant function because it's not going to change anything.
	bool IsInsideBoard(const Location& loc) const;

	void DrawBorder();
private:
	// Dimensions of the cells in the board, cells will be 20 by 20.
	static constexpr int dimension = 20;
	static constexpr int width = 32;
	static constexpr int height = 24;

	// Draw the Board at any arbitrary position on the screen because we'd like to center
	// it in our window.
	static constexpr int x = 70;
	static constexpr int y = 50;

	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2; // That's the padding between the Border and the actual Board.

	// Define Border Color.
	static constexpr Color borderColor = Colors::Blue;

	// Create a padding between cells.
	static constexpr int cellPadding = 1;	// 1 Pixel of padding between each cell.

	// Cache a reference to the graphics object so we don't have to pass it in ever time.
	Graphics& gfx;
};