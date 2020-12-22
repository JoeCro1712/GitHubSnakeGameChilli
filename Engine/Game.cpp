/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/


// *** NOTES FOR TUTORIAL 14 ***
// There is another data type specifier where you can declare data type called
// a * struct and sometimes people get confused about the difference between struct
// and class and here's the thing about them they are almost exactly the same
// except in a struct all the members default to public and in a class all the 
// members default to private that is the only difference between them, so they're
// basically interchangeble and the way that people usually differentiate between
// struct and class usage is struct is for very simple data types that don't really
// have any behavior don't have any complicated methods associated with them and 
// class is for more complicated objects components that have a lot of behavior a 
// lot of member functions.

// Cache means to store a local copy of someting for performance or convenience reasons
// (in this case convenience).

// Good idea is to test your components before you continue on with a new part of your
// program. Include Board in Game header and add Random Number Generator.


// ** AGGREGATE INITIALIZATION **
// Note that we can only initialize structs (or classes) with the {} initializer if they
// have no private data and specify no constructors. Otherwise, we have to use constructor
// functions ({} syntax can be used with constructors as well though).

// We're gonna need an array of Segments and we have to give it a size and so here's
// the problem we have to give this array an size but what size should we give it
// you see the snake is gonna start off with very few segments like maybe 3 or only
// 1 segment and as it eats thigns it grows so if we started off with the amount of
// segments that it needs at the beginning then when it eats some fruit you're not
// gonna have your array to be big enough but if you started of with like let's say 
// a 100 segments that's too many right you don't wanna start your game off with that
// so many so what's the solution?

// * Solution : The way that arrays work you can't change their size once you've created
// them in fact you have to set the size has to be known at the time you're compiling the 
// program and you can't make it grow or shrink after it's been made for sure so if you have
// a game and you want your Snake to be able to have a maximum of let's say a 100 segments
// then you have to make your array have a 100 elements that's just the way it is, now the
// way you handle this problem is at the beginnig you only have 3 elements let's say the 
// Snake starts with 3 segments so you only have 3 elements of array the 1st 3 elements that
// have valid values and you only use those frist 3 ones and rest of them are just treaded as
// garbage unused or at least not used yet so you never touch these when you're for example 
// drawing the Snake you only draw the first 3 and the rest ones they're not yet used, then
// as the Snake grows you mark some of these unused ones as used and in that sense your array
// grows or to be more precise the portion of array that you currently using grows and unused
// portion gets smaller.
// You got a couple of ways that you can mark off how the array is being used you can have an 
// element in the array whose value signifies that that's the end of the array so we call this 
// the Terminator element that is one way of doing it, the other way of doing it is you have a 
// variable you can call it "size" and that just stores the number of used elements (size[4]) 
// so right it would be 4 and the "size" it not only tells you howm many elements are currently
// used but it also happens to be an index into the next unused element so you can use it as an
// index to point to the first unused element and this is the method that we're gonna be using,
// we'll just remember the size or the number of used elements that we currently have in our array.

 
// ** SET UP THE FAIL CONDITION FOR THE SNAKE**//
// There's two main fail conditions :
// * 1st The Snake collides with itself
// * 2nd The Snake collides with the Wall.


// ** ASSIGMENT OPERATOR **
// For structures and for classes you can assing them to each other there's actually remember when
// we said there were a bunch of functions that are generated automatically by the compiler if you
// try to used them like for example the default constructor well there is also a function for assigning  
// one object to another that is generated by default by the compiler and that is called the ASSIGMENT OPERATOR.
// * Basically the way it works is it just takes all the data members and it assings them over from
// one Object to the other.


// const Location& GetLocation() const;
// Returning a reference is no problem here! But in GetNextHeadLocation(), the variable we're returning
// is a local, so it dies when the function returns, and thus if we return as reference there, we'd be 
// returning an invalid reference.


// ** DEFINE OPERATOR **
// Problem : "no operator "==" mathes these operands operand types are const Location == const Location
// so we have defined our own type called Location but Location it doesn't have any kind of operation 
// defined to compare two Locations to each other but in C++ we can define operations, we can define 
// the meanings of operators for objects and it's very common to define equivalence opertors for your objects.


// ** HOMEWORK FOR TUTORIAL 14 **
// * Adujstable Board position
// * Border drawn around board
// * Padding between board tiles
// * Display title screen
// * Give the Snake a pattern of colors for its segments
// * Make it so the Snake speeds up over time

#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device() ()),
	snake({2,2}),
	goal(rng, brd, snake)
	// comment added.
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameIsStarted)
	{
		if (!gameIsOver)
		{
			// Keyboard Input.
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0, -1 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0, 1 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1, 0 };
			}

			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1, 0 };
			}

			++snakeMoveCounter;
			if (snakeMoveCounter >= snakeMovePeriod)
			{
				// Reset the snakeMoveCounter.
				snakeMoveCounter = 0;

				const Location next = snake.GetNextHeadLocation(delta_loc);

				// Trigger the game over when the Snake isn't in Board or when the Snake 
				// collides with itself.
				// We're testing the next position of the Head against the old position of the
				// Snake but when the Head moves to that position the end of the Tail is also 
				// going to move so this test isn't really valid in this situtation.

				// What we should do is basically we want to do the test but we don't want to 
				// test the final Tail part, the reason for this is when the Snake moves the 
				// final Tail part is gonna go to the new position so it's going to become vacant
				// the end of the Tail occupied will become vacant after the Snake moves so we wanna
				// test but we want to exclude the very end of the Snake.
				if (!brd.IsInsideBoard(next) ||
					snake.IsInTileExceptEnd(next))
				{
					gameIsOver = true;
				}

				else
				{
					const bool eating = next == goal.GetLocation();
					if (eating)
					{
						snake.Grow();
					}
					// Update the Snake beased on delta location.
					snake.MoveBy(delta_loc);

					// If we're eating after we've moved
					if (eating)
					{
						goal.Respawn(rng, brd, snake);
					}
				}
			}
			++snakeSpeedUpCounter;
			if (snakeSpeedUpCounter >= snakeSpeedUpPeriod)
			{
				snakeSpeedUpCounter = 0;
				snakeMovePeriod = std::max(snakeMovePeriod - 1, snakeMovePeriodMin);
			}
		}
	}
	else
	{
		gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		snake.Draw(brd);
		goal.Draw(brd);

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
}
