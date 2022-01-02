#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"

class Tetris
{
private:
	int gameField[20][10] = { 0 };
	int score = 0;
	sf::Text scoreText;
	sf::Font font;
	sf::Text hints;
	sf::RenderWindow m_Window;
	Tetromino m_Tetromino;
	float timer = 0;
	float delay = 0.5;
	sf::Clock clock;
	void Input();
	void Draw();
	void Update();
	bool CheckCoordinates();
	void DisplayField();
	void LineDestroy();
	sf::Texture texture_frame;
	sf::Sprite sprite_frame;
	sf::Texture texture_background;
	sf::Sprite sprite_background;
	bool Defeat();
public:
	Tetris();
	void Start();
};