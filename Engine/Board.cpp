#include "Board.h"
#include <assert.h>

// Don't name your constructor parameters the same as the name of members that
// is a good thing but it's possible that you could name them the same.
Board::Board(Graphics & gfx)
	:
	// You can do this and it works fine and the reason is because in the class
	// initializer it's gonna assume that "gfx" are all members and so that's why
	// they won't alias to function parameter "gfx" and then inside the actual
	// parameters that used to initialize the members it's gonna pick the one
	// that's the closest scope which is going to be the locals.
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	// Adding some assertions in just some sanity checks to make sure that someone
	// isn't trying to draw outside of the board.
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int offsetX = x + borderWidth + borderPadding;
	const int offsetY = y + borderWidth + borderPadding;

	// This is basic math, you got a grid with cells 10x10 it's going to be first
	// one the top the y coordinate is gonna be 0 the next one is gonna be 10, 20, 30
	// so you just multiply the grid coordinate * dimension of the cell to get the 
	// position in screen space, then the width and the height are just gonna be the 
	// cell dimension and the color is just gonna be color "c" that was passed into
	// the function.
	// Add offsetX & offsetY to the starting positions of the rectangles.
	gfx.DrawRectDim(loc.x * dimension + offsetX + cellPadding, loc.y * dimension + offsetY + cellPadding, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

// We want to draw a Border around our Board, so the Border it's gonna be top left-hand corner of
// the Border is gonna be just the x and y position of the Board.First of all we're gonna draw it with
// four rectangles the top and the bottom rectangles are gonna span the entire width and the left and 
// right rectangles are going to be the left side and the right side minus the parts that are covered
// by the top and the bottom rectangles. 
// So we're drawing these rectangles they're gonna have a set border width which is gonna be another
// constant that we define and we've got calculate their dimensions or their position of the points,
// we've got two versions of draw rect we can use and probably we use the version that takes left, right,
// top and bottom, so what we're gonna do is we're gonna recalculate the top the left the right and the
// bottom cooridinates for this outer region of the border nad the we're use that to claculate the data
// values needed to draw the Border rectangles.
// Generally when you specify a rectangle you specify exclusive coordinates for the bottom and the right
// meaning the value that you specify on the right it's gonna draw up to but not including that coordinate
// position and the same at the bottom it's gonna draw up to but not including the bottom.
void Board::DrawBorder()
{
	const int topBorderSide = y;
	const int leftBorderSide = x;
	// Multipy whole quantity by two because there's two borders and two padding's between the top and the bottom
	// plus height times dimension which is the dimension of a tile int the grid of tiles.
	const int bottomBorderSide = topBorderSide + (borderWidth + borderPadding) * 2 + height * dimension;
	const int rightBorderSide = leftBorderSide + (borderWidth + borderPadding) * 2 + width * dimension;

	// Draw those four rectangles.
	// TOP
	gfx.DrawRect(leftBorderSide, topBorderSide, rightBorderSide, topBorderSide + borderWidth, borderColor);

	// LEFT
	gfx.DrawRect(leftBorderSide, topBorderSide + borderWidth, leftBorderSide + borderWidth, bottomBorderSide - borderWidth, borderColor);

	// RIGHT
	gfx.DrawRect(rightBorderSide - borderWidth, topBorderSide + borderWidth, rightBorderSide, bottomBorderSide - borderWidth, borderColor);

	// BOTTOM
	gfx.DrawRect(leftBorderSide, bottomBorderSide - borderWidth, rightBorderSide, bottomBorderSide, borderColor);
}
