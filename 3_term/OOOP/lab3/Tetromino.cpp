#include "Tetromino.h"

Tetromino::Tetromino() {
	SetNewTetromino();
}

int Tetromino::RandNumber() {
	static std::random_device rd;
	static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
	static std::mt19937_64 gen(seed);
	std::uniform_int_distribution<int> dist(1, 7);

	return dist(gen);
}

sf::Sprite Tetromino::getSprite(int num) {
	Cube_Sprite[num].move(40, 50);
	return Cube_Sprite[num];
}

sf::Vector2i Tetromino::getCoordinates(int num) {
	return coordinates[num];
}

sf::Vector2i Tetromino::getExtra(int num) {
	return extra[num];
}

int Tetromino::getNumber() {
	return number;
}

void Tetromino::SetFigure() {
	int n = number - 1;
	for (int i = 0; i < 4; i++) {
		coordinates[i].x = (figures[n][i] % 2) + 4;
		coordinates[i].y = figures[n][i] / 2;
	}
	for (int i = 0; i < 4; i++) {
		Cube_Sprite[i].setPosition(coordinates[i].x * 25, coordinates[i].y * 25);
	}
}

void Tetromino::moveLeft() {
	for (int i = 0; i < 4; i++) {
		extra[i] = coordinates[i];
		coordinates[i].x -= 1;
	}
}

void Tetromino::moveRight() {
	for (int i = 0; i < 4; i++) {
		extra[i] = coordinates[i];
		coordinates[i].x += 1;
	}
}

void Tetromino::moveDown() {
	for (int i = 0; i < 4; i++) {
		extra[i] = coordinates[i];
		coordinates[i].y += 1;
	}
}
void Tetromino::Rotate() {
	sf::Vector2i center = coordinates[1]; // указываем центр вращения
	for (int i = 0; i < 4; i++) {
		extra[i] = coordinates[i];
		int x = coordinates[i].y - center.y; // y - y0
		int y = coordinates[i].x - center.x; // x - x0
		coordinates[i].x = center.x - x;
		coordinates[i].y = center.y + y;
	}
}

void Tetromino::Update() {
	for (int i = 0; i < 4; i++) {
		Cube_Sprite[i].setPosition(coordinates[i].x * 25, coordinates[i].y * 25);
	}
}

void Tetromino::RestoreCoordinates() {
	for (int i = 0; i < 4; i++) {
		coordinates[i] = extra[i];
	}
}

void Tetromino::SetNewTetromino() {
	Cube_Texture.loadFromFile("cubes.png");
	number = RandNumber();
	int color = RandNumber();
	for (int i = 0; i < 4; i++) {
		Cube_Sprite[i].setTexture(Cube_Texture);
		Cube_Sprite[i].setTextureRect(sf::IntRect((color- 1) * 25, 0, 25, 25));
	}
	SetFigure();
}