#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

class Tetromino
{
private:
	sf::Sprite Cube_Sprite[4];
	sf::Texture Cube_Texture;
	int figures[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};
	sf::Vector2i extra[4];
	sf::Vector2i coordinates[4];
	int RandNumber();
	int number;
public:
	Tetromino();
	sf::Sprite getSprite(int num);
	sf::Vector2i getCoordinates(int num);
	sf::Vector2i getExtra(int num);
	int getNumber();
	void SetFigure();
	void moveLeft();
	void moveRight();
	void moveDown();
	void Rotate();
	void Update();
	void RestoreCoordinates();
	void SetNewTetromino();
};