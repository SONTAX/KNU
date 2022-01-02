#include "Tetris.h"

Tetris::Tetris() {
	m_Window.create(sf::VideoMode(480, 720), "TETRIS");
	texture_frame.loadFromFile("frame.png");
	sprite_frame.setTexture(texture_frame);
	sprite_frame.move(40, 50);
	font.loadFromFile("ArialBlack.ttf");
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.move(40, 0);
	hints.setFont(font);
	hints.setFillColor(sf::Color::Black);
	sf::String string = "Left - move left\t\tUp - rotate\nRight - move right\t\Down - force down\nR - start new game";
	hints.setString(string);
	hints.move(20, 600);
	hints.setCharacterSize(20);
	texture_background.loadFromFile("background.jpg");
	sprite_background.setTexture(texture_background);
}

void Tetris::Draw() {
	m_Window.clear(sf::Color::White);
	m_Window.draw(sprite_background);
	m_Window.draw(sprite_frame);
	DisplayField();
	sf::String string = "Your score: ";
	string += std::to_string(score);
	scoreText.setString(string);
	m_Window.draw(m_Tetromino.getSprite(0));
	m_Window.draw(m_Tetromino.getSprite(1));
	m_Window.draw(m_Tetromino.getSprite(2));
	m_Window.draw(m_Tetromino.getSprite(3));
	m_Window.draw(scoreText);
	m_Window.draw(hints);
	m_Window.display();
}

void Tetris::Start() {
    while (m_Window.isOpen()) {
		if (Defeat()) {
			sf::Event event;
			while (m_Window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::R) {
						score = 0;
						for (int i = 0; i < 20; i++) {
							for (int j = 0; j < 10; j++) {
								gameField[i][j] = 0;
							}
						}
						m_Window.clear(sf::Color::White);
						m_Tetromino.SetNewTetromino();
					}
				}
			}
			sf::String lost = "GAME OVER\n\n\nYour score is\n";
			lost += std::to_string(score);
			sf::Text defeattext(lost, font, 50);
			defeattext.setFillColor(sf::Color::Black);
			defeattext.move(50, 175);
			m_Window.clear(sf::Color::White);
			m_Window.draw(defeattext);
			m_Window.display();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			score = 0;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 10; j++) {
					gameField[i][j] = 0;
				}
			}
			m_Window.clear(sf::Color::White);
			m_Tetromino.SetNewTetromino();
		}
		else {

			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			LineDestroy();
			Input();
			Update();
			Draw();
		}
    }
}

void Tetris::Input() {
	sf::Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				m_Tetromino.Rotate();
			}
			else if (event.key.code == sf::Keyboard::Left) {
				m_Tetromino.moveLeft();
			}
			else if (event.key.code == sf::Keyboard::Right) {
				m_Tetromino.moveRight();
			}
			else if (event.key.code == sf::Keyboard::Down) {
				delay = 0.05;
			}
		}
	}
	if (!CheckCoordinates()) {
		m_Tetromino.RestoreCoordinates();
	}
	m_Tetromino.Update();
}

void Tetris::Update() {
	if (timer > delay) {
		m_Tetromino.moveDown();
		if (!CheckCoordinates()) {
			for (int i = 0; i < 4; i++) {
				sf::Vector2i b = m_Tetromino.getExtra(i);
				gameField[b.y][b.x] = m_Tetromino.getNumber();
				m_Tetromino.SetNewTetromino();
				delay = 0.5;
			}
		}
		timer = 0;
	}
}

bool Tetris::CheckCoordinates() {
	for (int i = 0; i < 4; i++) {
		sf::Vector2i a = m_Tetromino.getCoordinates(i);
		if (a.x < 0 || a.x >= 10 || a.y >= 20) {
			return false;
		}
		else if (gameField[a.y][a.x]) {
			return false;
		}
	}
	return true;
}

void Tetris::DisplayField() {
	sf::Texture texture;
	texture.loadFromFile("cubes.png");
	sf::Sprite sprite;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (gameField[i][j] != 0) {
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(0, gameField[i][j] * 25, 25, 25));
				sprite.setPosition(j * 25, i * 25);
				sprite.move(40, 50);
				m_Window.draw(sprite);
			}
		}
	}
}

void Tetris::LineDestroy() {
	int k = 19;
	int destroyed = 0;
	for (int i = 19; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < 10; j++) {
			if (gameField[i][j]) {
				count++;
			}
			gameField[k][j] = gameField[i][j];
		}
		if (count < 10) {
			k--;
		}
		else {
			destroyed++;
		}
	}
	switch (destroyed)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 700;
		break;
	case 4:
		score += 1500;
		break;
	}
}

bool Tetris::Defeat() {
	for (int i = 2; i < 6; i++) {
		if (gameField[2][i] != 0) {
			return true;
		}
	}
	return false;
}