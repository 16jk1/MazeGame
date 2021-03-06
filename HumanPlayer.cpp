#pragma once
#include "HumanPlayer.h"
#include "MazeConstructor.h"
#include "MazeSquare.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#define moveSpeed .1
#define SQUARE_SIZE 40 	// Length of each square of the maze

#define SIZE 15

// Constructor - takes in file name of the sprite texture and the maze that the player will be placed in
HumanPlayer::HumanPlayer(const sf::Texture& imagePath, vector<vector<MazeSquare>> Maze, sf::Vector2f start, int xgoal, int ygoal) {

	xfinal = xgoal;
	yfinal = ygoal;
	xf = xgoal;
	yf = ygoal;
	mSprite.setTexture(imagePath);
	currentMaze = Maze;
	// Sets the current square the player is in
	x = 0;
	y = 0;
	getx = x;
	gety = y;
	// Set default movement speed
	//moveSpeed = 0.8;
	currentSquare = currentMaze[x][y];
	isMoving = false;
	canInput = true;
	isEnd = false;
	// Set the starting position of the player
	//mSprite.setPosition(15.0f, 15.0f);
	mSprite.setPosition(start.x, start.y);
	// Sets the size of the sprite
	mSprite.setTextureRect(sf::IntRect(2.5, 2.5, 20, 20));
}

HumanPlayer::~HumanPlayer() {
    // TODO Auto-generated destructor stub
	//delete &mSprite;

}

void HumanPlayer::getImage(const sf::Texture& imagePath){
	mSprite.setTexture(imagePath);
}
void HumanPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}
/*
// Accessor - returns current movement speed
float getMoveSpeed() const {
	return moveSpeed;
}

// Mutator - changes current movement speed
void changeMoveSpeed(const float newMoveSpeed) {
	moveSpeed = newMoveSpeed;
}
*/
/* MOVEMENT
 * The Player object moves from square to square
 * Animation speed is dictated by MOVE_SPEED
*/

void HumanPlayer::moveUp(sf::Time timeChange) {
	if (!currentSquare.upWall) {
		y--;
		getx = x;
		gety = y;
		currentSquare = currentMaze[x][y];

		float newYPos = mSprite.getPosition().y - SQUARE_SIZE;
		// Move to the square above
		isMoving = true;
		while (mSprite.getPosition().y >= newYPos) {
			mSprite.move(0, -moveSpeed);
		}
		//isMoving = false;
		//delete &mSprite;
		if (currentMaze[x][y] == currentMaze[xfinal][yfinal])
			isEnd = true;
	}

	canInput = true;
}

void HumanPlayer::moveDown(sf::Time timeChange) {
	if (!currentSquare.downWall) {
		y++;
		getx = x;
		gety = y;
		currentSquare = currentMaze[x][y];

		float newYPos = mSprite.getPosition().y + SQUARE_SIZE;
		// Move to the square below
		//isMoving = true;
		while (mSprite.getPosition().y <= newYPos) {
			mSprite.move(0, moveSpeed);
		}
		isMoving = false;
		//delete &mSprite;
		if (currentMaze[x][y] == currentMaze[xfinal][yfinal]){
			isEnd = true;
		}
	}

	canInput = true;
}

void HumanPlayer::moveLeft(sf::Time timeChange) {
	if (!currentSquare.leftWall ) {
		//cout<<x<<endl;
		x--;
		getx = x;
		gety = y;
		currentSquare = currentMaze[x][y];
		float newXPos = mSprite.getPosition().x - SQUARE_SIZE;
		// Move to the square to the left
		//isMoving = false;
		while (mSprite.getPosition().x >= newXPos) {
			mSprite.move(-moveSpeed, 0);
		}
		//isMoving = false;
		//delete &mSprite;
		if (currentMaze[x][y] == currentMaze[xfinal][yfinal]){
			isEnd = true;
		}
	}

	canInput = true;
}

void HumanPlayer::moveRight(sf::Time timeChange) {
	if (!currentSquare.rightWall) {
		//isMoving = true;
		x++;
		getx = x;
		gety = y;
		currentSquare = currentMaze[x][y];

		float newXPos = mSprite.getPosition().x + SQUARE_SIZE;
		// Move to the square to the right
		while (mSprite.getPosition().x <= newXPos) {
			mSprite.move(moveSpeed, 0);
		}
		//isMoving = false;
		//delete &mSprite;
		if (currentMaze[x][y] == currentMaze[xfinal][yfinal]){
			isEnd = true;
		}
	}

	canInput = true;
}
