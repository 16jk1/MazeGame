/*
 * ScreenController.cpp
 *
 *  Created on: Nov 2, 2018
 *      Author: Adrian
 */
#include "ScreenController.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "MazeConstructor.h"

InstructionsScreen::InstructionsScreen(
		vector<sf::Keyboard::Key> player1Controls,
		vector<sf::Keyboard::Key> player2Controls) {
	this->player1Controls = player1Controls;
	this->player2Controls = player2Controls;
}
SetupScreen::SetupScreen(vector<sf::Keyboard::Key> player1Controls,
		vector<sf::Keyboard::Key> player2Controls, string scoreFile) {
	this->player1Controls = player1Controls;
	this->player2Controls = player2Controls;
	highScoreFile = scoreFile;
}
TitleScreen::TitleScreen() {
	player1Controls.push_back(sf::Keyboard::Key::W);
	player1Controls.push_back(sf::Keyboard::Key::A);
	player1Controls.push_back(sf::Keyboard::Key::S);
	player1Controls.push_back(sf::Keyboard::Key::D);
	player1Controls.push_back(sf::Keyboard::Key::F);

	player2Controls.push_back(sf::Keyboard::Key::U);
	player2Controls.push_back(sf::Keyboard::Key::H);
	player2Controls.push_back(sf::Keyboard::Key::J);
	player2Controls.push_back(sf::Keyboard::Key::K);
	player2Controls.push_back(sf::Keyboard::Key::L);
	highScoreFile = "ScoreFile.txt";
}

void TitleScreen::StartGame(sf::RenderWindow& window, sf::Music& mus) {
	StartUp(window);
	sf::SoundBuffer buffer;
	sf::Sound click;
	buffer.loadFromFile("sounds/click.wav");
	click.setBuffer(buffer);
	sf::Vector2<int> mou;
	vector<sf::Text> buttonText;
	vector<sf::RectangleShape> buttonBlock;
	sf::Font font;
	sf::Vector2u winSize = window.getSize();
	font.loadFromFile("text/olympiccarriersuperital.ttf");

	for (int i = 0; i < 3; i++) {
		buttonText.push_back(sf::Text());
		buttonBlock.push_back(sf::RectangleShape(sf::Vector2f(620, 50)));
	}

	sf::Text text1;

	text1.setString("Maze of Bad Decisions");
	text1.setCharacterSize(37);
	text1.setFont(font);
	text1.setFillColor(sf::Color::Cyan);
	sf::FloatRect temp = text1.getLocalBounds();
	text1.setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
	text1.setPosition(winSize.x / 2, winSize.y / 2 - 200);
	buttonText[0].setString("Start Game");
	buttonText[1].setString("Instructions/Controls");
	buttonText[2].setString("Exit");

	for (int i = 0; i < 3; i++) {
		buttonText[i].setCharacterSize(24);
		buttonText[i].setFont(font);
		buttonText[i].setPosition(winSize.x / 2, winSize.y / 2 + (60.f * i));
		buttonText[i].setFillColor(sf::Color(255, 20, 147));
		buttonBlock[i].setFillColor(sf::Color::Cyan);
		buttonBlock[i].setOutlineColor(sf::Color::Red);
		buttonBlock[i].setPosition(winSize.x / 2, winSize.y / 2 + (60.f * i));
		temp = buttonBlock[i].getLocalBounds();
		buttonBlock[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		temp = buttonText[i].getLocalBounds();
		buttonText[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
	}

	while (window.isOpen()) {
		mou = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			for (int i = 0; i < 3; i++) {
				if (mou.x > winSize.x / 2 - 310 && mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 - 25 + (60.f * i)
						&& mou.y < winSize.y / 2 + 25 + (60.f * i)) {
					buttonBlock[i].setOutlineThickness(5);
				} else {
					buttonBlock[i].setOutlineThickness(0);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (mou.x > winSize.x / 2 - 310 && mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 - 25
						&& mou.y < winSize.y / 2 + 25) {
					click.play();
					SetupScreen setup(player1Controls, player2Controls,
							highScoreFile);
					setup.SetupGame(window);
					click.play();
				} else if (mou.x > winSize.x / 2 - 310
						&& mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 + 35
						&& mou.y < winSize.y / 2 + 85) {
					click.play();
					InstructionsScreen instruction(player1Controls,
							player2Controls);
					instruction.Open(window, mus);
					player1Controls = instruction.player1Controls;
					player2Controls = instruction.player2Controls;
					click.play();
				} else if (mou.x > winSize.x / 2 - 310
						&& mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 + 95
						&& mou.y < winSize.y / 2 + 145) {
					click.play();
					window.close();
				}
			}
		}

		window.clear();
		window.draw(text1);
		for (int i = 0; i < 3; i++) {
			window.draw(buttonBlock[i]);
			window.draw(buttonText[i]);
		}
		window.display();
	}
}

void InstructionsScreen::Open(sf::RenderWindow& window, sf::Music& mus) {
	sf::Vector2<int> mou;
	vector<sf::Text> controlText;
	vector<vector<sf::Text>> playerText;
	vector<vector<sf::RectangleShape>> playerBlock;
	vector<sf::Text> menuText;
	vector<sf::RectangleShape> menuBlock;
	sf::Font font;
	sf::Vector2u winSize = window.getSize();
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::Sound click;
	sf::Sound error;
	sf::Sound confirm;
	buffer.loadFromFile("sounds/click.wav");
	buffer2.loadFromFile("sounds/ringout.wav");
	buffer3.loadFromFile("sounds/confirm.wav");
	click.setBuffer(buffer);
	error.setBuffer(buffer2);
	confirm.setBuffer(buffer3);
	font.loadFromFile("text/olympiccarriersuperital.ttf");

	int musVol = mus.getVolume() + 1;

	for (int i = 0; i < 2; i++) {
		vector<sf::Text> textVector;
		vector<sf::RectangleShape> blockVector;
		for (int j = 0; j < 6; j++) {
			textVector.push_back(sf::Text());
			blockVector.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
		}
		playerText.push_back(textVector);
		playerBlock.push_back(blockVector);
	}
	for (int i = 0; i < 6; i++) {
		controlText.push_back(sf::Text());
	}
	for (int i = 0; i < 3; i++) {
		menuText.push_back(sf::Text());
		menuBlock.push_back(sf::RectangleShape(sf::Vector2f(180, 50)));
	}

	controlText[0].setString("Move Up");
	controlText[1].setString("Move Left");
	controlText[2].setString("Move Down");
	controlText[3].setString("Move Right");
	controlText[4].setString("Use Item");
	controlText[5].setString("AUDIO: " + to_string(musVol));
	menuText[0].setString("Restore Default");
	menuText[1].setString("Character's Story");
	menuText[2].setString("Exit");

	for (int i = 0; i < 5; i++) {
		playerText[0][i].setString(fromKtoS(player1Controls[i]));
		playerText[1][i].setString(fromKtoS(player2Controls[i]));
		controlText[i].setCharacterSize(24);
		controlText[i].setFont(font);
		sf::FloatRect temp = controlText[i].getLocalBounds();
		controlText[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		controlText[i].setPosition(winSize.x / 2,
				winSize.y / 2 - 165.f + (60.f * i));
		controlText[i].setFillColor(sf::Color(255, 20, 147));
	}

	playerText[0][5].setString("-");
	playerText[1][5].setString("+");
	controlText[5].setCharacterSize(24);
	controlText[5].setFont(font);
	sf::FloatRect temp = controlText[5].getLocalBounds();
	controlText[5].setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
	controlText[5].setPosition(winSize.x / 2,
			winSize.y / 2 - 165.f + (60.f * 5));
	controlText[5].setFillColor(sf::Color(255, 20, 147));

	for (int i = 0; i < 3; i++) {
		menuBlock[i].setFillColor(sf::Color::Cyan);
		menuBlock[i].setOutlineColor(sf::Color::Red);
		menuBlock[i].setPosition(winSize.x / 2 - 200.f + (200.f * i),
				winSize.y / 2 + 245);
		menuText[i].setCharacterSize(17);
		menuText[i].setFont(font);
		sf::FloatRect temp = menuText[i].getLocalBounds();
		menuText[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		temp = menuBlock[i].getLocalBounds();
		menuBlock[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		menuText[i].setPosition(winSize.x / 2 - 200.f + (200.f * i),
				winSize.y / 2 + 245);
		menuText[i].setFillColor(sf::Color(255, 20, 147));
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 6; i++) {
			playerText[j][i].setCharacterSize(24);
			playerText[j][i].setFont(font);
			playerText[j][i].setPosition(winSize.x / 2 - 140 + (280.f * j),
					winSize.y / 2 - 165 + (60.f * i));
			playerText[j][i].setFillColor(sf::Color(255, 20, 147));
			playerBlock[j][i].setFillColor(sf::Color::Cyan);
			playerBlock[j][i].setOutlineColor(sf::Color::Red);
			playerBlock[j][i].setPosition(winSize.x / 2 - 140 + (280.f * j),
					winSize.y / 2 - 165 + (60.f * i));
			sf::FloatRect temp = playerText[j][i].getLocalBounds();
			playerText[j][i].setOrigin(temp.left + temp.width / 2.0f,
					temp.top + temp.height / 2.0f);
			temp = playerBlock[j][i].getLocalBounds();
			playerBlock[j][i].setOrigin(temp.left + temp.width / 2.0f,
					temp.top + temp.height / 2.0f);
		}
	}
	bool showInstruct = true;
	int menuEffect = -1;
	int controlEffect = -1;
	while (showInstruct) {
		mou = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				showInstruct = false;
			}
			if ((event.type == sf::Event::KeyPressed
					&& event.text.unicode == sf::Keyboard::Escape)
					|| (menuEffect == 2)) {
				showInstruct = false;
			} else if (event.type == sf::Event::KeyPressed
					&& controlEffect >= 0) {
				bool unused = true;
				for (int i = 0; i < 5; i++) {
					if ((i != controlEffect)
							&& (event.text.unicode == player1Controls[i])) {
						unused = false;
						error.play();
					}
				}
				for (int i = 0; i < 5; i++) {
					if ((i + 5 != controlEffect)
							&& (event.text.unicode == player2Controls[i])) {
						unused = false;
						error.play();
					}
				}

				if (unused) {
					confirm.play();
					if (controlEffect < 5) {
						player1Controls[controlEffect] = event.key.code;
						playerText[0][controlEffect].setString(
								fromKtoS(event.key.code));
						playerText[0][controlEffect].setCharacterSize(24);
						sf::FloatRect temp =
								playerText[0][controlEffect].getLocalBounds();
						while (temp.width > 50) {
							playerText[0][controlEffect].setCharacterSize(
									playerText[0][controlEffect].getCharacterSize()
											- 1);
							temp =
									playerText[0][controlEffect].getLocalBounds();
						}
						playerText[0][controlEffect].setOrigin(
								temp.left + temp.width / 2.0f,
								temp.top + temp.height / 2.0f);
					} else {
						player2Controls[controlEffect - 5] = event.key.code;
						playerText[1][controlEffect - 5].setString(
								fromKtoS(event.key.code));
						playerText[1][controlEffect - 5].setCharacterSize(24);
						sf::FloatRect temp =
								playerText[1][controlEffect - 5].getLocalBounds();
						while (temp.width > 50) {
							playerText[1][controlEffect - 5].setCharacterSize(
									playerText[1][controlEffect - 5].getCharacterSize()
											- 1);
							temp =
									playerText[1][controlEffect - 5].getLocalBounds();
						}
						playerText[1][controlEffect - 5].setOrigin(
								temp.left + temp.width / 2.0f,
								temp.top + temp.height / 2.0f);
					}
				}
				controlEffect = -1;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				for (int j = 0; j < 2; j++) {
					for (int i = 0; i < 5; i++) {
						if ((mou.x > winSize.x / 2 - 165 + (280.f * j))
								&& (mou.x < winSize.x / 2 - 115 + (280.f * j))
								&& mou.y > winSize.y / 2 - 190 + (60.f * i)
								&& mou.y < winSize.y / 2 - 140 + (60.f * i)) {
							controlEffect = i + (5 * j);
							click.play();
						}
					}
				}

				for (int j = 0; j < 2; j++) {
					if ((mou.x > winSize.x / 2 - 165 + (280.f * j))
							&& (mou.x < winSize.x / 2 - 115 + (280.f * j))
							&& mou.y > winSize.y / 2 - 190 + (60.f * 5)
							&& mou.y < winSize.y / 2 - 140 + (60.f * 5)) {
						click.play();
						if (j == 0 && musVol != 0){
							musVol = musVol - 1;
						} else if (j == 1) {
							musVol = musVol + 1;
						}
						mus.setVolume(musVol);
						controlText[5].setString("AUDIO: " + to_string(musVol));
						controlText[5].setCharacterSize(24);
						controlText[5].setFont(font);
						sf::FloatRect temp = controlText[5].getLocalBounds();
						controlText[5].setOrigin(temp.left + temp.width / 2.0f,
								temp.top + temp.height / 2.0f);
						controlText[5].setPosition(winSize.x / 2,
								winSize.y / 2 - 165.f + (60.f * 5));

					}
				}

				for (int i = 0; i < 3; i++) {
					if ((mou.x > winSize.x / 2 - 290.f + (200.f * i))
							&& (mou.x < winSize.x / 2 - 110.f + (200.f * i))
							&& (mou.y > winSize.y / 2 + 220)
							&& (mou.y < winSize.y / 2 + 270)) {
						menuEffect = i;
						if (i != 2) {
							click.play();
						}
					}
				}
			}

			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < 5; i++) {
					if ((mou.x > winSize.x / 2 - 165 + (280.f * j))
							&& (mou.x < winSize.x / 2 - 115 + (280.f * j))
							&& mou.y > winSize.y / 2 - 190 + (60.f * i)
							&& mou.y < winSize.y / 2 - 140 + (60.f * i)) {
						playerBlock[j][i].setOutlineThickness(3);
					} else {
						playerBlock[j][i].setOutlineThickness(0);
					}
				}
			}

			for (int j = 0; j < 2; j++) {
				if ((mou.x > winSize.x / 2 - 165 + (280.f * j))
						&& (mou.x < winSize.x / 2 - 115 + (280.f * j))
						&& mou.y > winSize.y / 2 - 190 + (60.f * 5)
						&& mou.y < winSize.y / 2 - 140 + (60.f * 5)) {
					playerBlock[j][5].setOutlineThickness(3);
				} else {
					playerBlock[j][5].setOutlineThickness(0);
				}
			}

			for (int i = 0; i < 3; i++) {
				if ((mou.x > winSize.x / 2 - 290.f + (200.f * i))
						&& (mou.x < winSize.x / 2 - 110.f + (200.f * i))
						&& (mou.y > winSize.y / 2 + 220)
						&& (mou.y < winSize.y / 2 + 270)) {
					menuBlock[i].setOutlineThickness(3);
				} else {
					menuBlock[i].setOutlineThickness(0);
				}
			}
		}

		for (int i = 0; i < 10; i++) {
			if (i == controlEffect && controlEffect < 5) {
				playerBlock[0][controlEffect].setOutlineThickness(3);
				playerBlock[0][controlEffect].setOutlineColor(sf::Color::Blue);
			} else if (i == controlEffect && controlEffect >= 5) {
				playerBlock[1][controlEffect - 5].setOutlineThickness(3);
				playerBlock[1][controlEffect - 5].setOutlineColor(
						sf::Color::Blue);
			} else if (i < 5) {
				playerBlock[0][i].setOutlineColor(sf::Color::Red);
			} else {
				playerBlock[1][i - 5].setOutlineColor(sf::Color::Red);
			}
		}

		if (menuEffect == 0) {
			player1Controls[0] = (sf::Keyboard::Key::W);
			player1Controls[1] = (sf::Keyboard::Key::A);
			player1Controls[2] = (sf::Keyboard::Key::S);
			player1Controls[3] = (sf::Keyboard::Key::D);
			player1Controls[4] = (sf::Keyboard::Key::F);

			player2Controls[0] = (sf::Keyboard::Key::U);
			player2Controls[1] = (sf::Keyboard::Key::H);
			player2Controls[2] = (sf::Keyboard::Key::J);
			player2Controls[3] = (sf::Keyboard::Key::K);
			player2Controls[4] = (sf::Keyboard::Key::L);

			for (int i = 0; i < 5; i++) {
				playerText[1][i].setString(fromKtoS(player2Controls[i]));
				playerText[1][i].setCharacterSize(24);
				sf::FloatRect temp = playerText[1][i].getLocalBounds();
				while (temp.width > 50) {
					playerText[1][i].setCharacterSize(
							playerText[1][i].getCharacterSize() - 1);
					temp = playerText[1][i].getLocalBounds();
				}
				playerText[1][i].setOrigin(temp.left + temp.width / 2.0f,
						temp.top + temp.height / 2.0f);
			}
			for (int i = 0; i < 5; i++) {
				playerText[0][i].setString(fromKtoS(player1Controls[i]));
				playerText[0][i].setCharacterSize(24);
				sf::FloatRect temp = playerText[0][i].getLocalBounds();
				while (temp.width > 50) {
					playerText[0][i].setCharacterSize(
							playerText[0][i].getCharacterSize() - 1);
					temp = playerText[0][i].getLocalBounds();
				}
				playerText[0][i].setOrigin(temp.left + temp.width / 2.0f,
						temp.top + temp.height / 2.0f);
			}

			menuEffect = -1;
		} else if (menuEffect == 1) {
			CharacterPage(window);
			click.play();
			menuEffect = -1;
		}

		window.clear();
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 6; i++) {
				window.draw(playerBlock[j][i]);
				window.draw(playerText[j][i]);
			}
		}
		for (int i = 0; i < 6; i++) {
			window.draw(controlText[i]);
		}
		for (int i = 0; i < 3; i++) {
			window.draw(menuBlock[i]);
			window.draw(menuText[i]);
		}
		window.display();
	}
}

void SetupScreen::SetupGame(sf::RenderWindow& window) {
	sf::Vector2<int> mou;
	vector<sf::Text> buttonText;
	vector<sf::RectangleShape> buttonBlock;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound click;
	buffer.loadFromFile("sounds/click.wav");
	click.setBuffer(buffer);
	sf::Vector2u winSize = window.getSize();
	font.loadFromFile("text/olympiccarriersuperital.ttf");

	for (int i = 0; i < 3; i++) {
		buttonText.push_back(sf::Text());
		buttonBlock.push_back(sf::RectangleShape(sf::Vector2f(620, 50)));
	}

	sf::Text text1;

	text1.setString("Maze of Bad Decisions");
	text1.setCharacterSize(37);
	text1.setFont(font);
	text1.setFillColor(sf::Color::Cyan);
	sf::FloatRect temp = text1.getLocalBounds();
	text1.setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
	text1.setPosition(winSize.x / 2, winSize.y / 2 - 200);
	buttonText[0].setString("Player VS. AI");
	buttonText[1].setString("Player VS. Player");
	buttonText[2].setString("Exit");

	for (int i = 0; i < 3; i++) {
		buttonText[i].setCharacterSize(24);
		buttonText[i].setFont(font);
		buttonText[i].setPosition(winSize.x / 2, winSize.y / 2 + (60.f * i));
		buttonText[i].setFillColor(sf::Color(255, 20, 147));
		buttonBlock[i].setFillColor(sf::Color::Cyan);
		buttonBlock[i].setOutlineColor(sf::Color::Red);
		buttonBlock[i].setPosition(winSize.x / 2, winSize.y / 2 + (60.f * i));
		temp = buttonBlock[i].getLocalBounds();
		buttonBlock[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		temp = buttonText[i].getLocalBounds();
		buttonText[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
	}
	bool stayOpen = true;
	while (stayOpen) {
		mou = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				stayOpen = false;
			}

			for (int i = 0; i < 3; i++) {
				if (mou.x > winSize.x / 2 - 310 && mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 - 25 + (60.f * i)
						&& mou.y < winSize.y / 2 + 25 + (60.f * i)) {
					buttonBlock[i].setOutlineThickness(5);
				} else {
					buttonBlock[i].setOutlineThickness(0);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (mou.x > winSize.x / 2 - 310 && mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 - 25
						&& mou.y < winSize.y / 2 + 25) {
					click.play();
					GameScreen game;
					game.Game(window, true, player1Controls, player2Controls);
				} else if (mou.x > winSize.x / 2 - 310
						&& mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 + 35
						&& mou.y < winSize.y / 2 + 85) {
					click.play();
					GameScreen game;
					game.Game(window, false, player1Controls, player2Controls);
				} else if (mou.x > winSize.x / 2 - 310
						&& mou.x < winSize.x / 2 + 310
						&& mou.y > winSize.y / 2 + 95
						&& mou.y < winSize.y / 2 + 145) {
					stayOpen = false;
				}
			}
		}

		window.clear();
		window.draw(text1);
		for (int i = 0; i < 3; i++) {
			window.draw(buttonBlock[i]);
			window.draw(buttonText[i]);
		}
		window.display();
	}
}

void TitleScreen::StartUp(sf::RenderWindow& window) { //TODO: Consider decreasing sprite frames
	sf::Texture texture;
	sf::Texture texture2;
	sf::Sprite sprite;
	sf::Sprite sprite2;
	sf::Vector2u winSize = window.getSize();
	texture.loadFromFile("images/QueensLogo.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.75f, 0.75f));
	texture2.loadFromFile("images/Logo.png");
	sprite2.setTexture(texture2);
	sprite2.setScale(sf::Vector2f(0.75f, 0.75f));
	sf::FloatRect temp = sprite.getLocalBounds();
	sprite.setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
	temp = sprite2.getLocalBounds();
	sprite2.setOrigin(temp.left + temp.width / 2.0f,
			temp.top + temp.height / 2.0f);
	sprite.setPosition(winSize.x / 2, winSize.y / 2);
	sprite2.setPosition(winSize.x / 2, winSize.y / 2);

	sf::Event event;
	bool stayOpen = true;
	int phase = 1;
	int i = 0;
	sprite2.setColor(sf::Color(255, 255, 255, i / 10));

	while (stayOpen && phase == 1) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				stayOpen = false;
			}
			if (event.type == sf::Event::KeyPressed) {
				stayOpen = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				stayOpen = false;
			}
		}

		sprite.setColor(sf::Color(255, 255, 255, i / 2));
		window.clear();
		window.draw(sprite);
		window.display();
		i++;
		if (i >= 510) {
			phase = 2;
		}
	}
	while (stayOpen && phase == 2) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				stayOpen = false;
			}
			if (event.type == sf::Event::KeyPressed) {
				stayOpen = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				stayOpen = false;
			}
		}

		sprite.setColor(sf::Color(255, 255, 255, i / 2));
		window.clear();
		window.draw(sprite);
		window.display();
		i--;
		if (i <= 0) {
			stayOpen = false;
		}
	}

	stayOpen = true;
	phase = 1;
	i = 0;
	while (stayOpen && phase == 1) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				stayOpen = false;
			}
			if (event.type == sf::Event::KeyPressed) {
				stayOpen = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				stayOpen = false;
			}
		}

		sprite2.setColor(sf::Color(255, 255, 255, i / 2));
		window.clear();
		window.draw(sprite2);
		window.display();
		i++;
		if (i >= 510) {
			phase = 2;
		}
	}
	while (stayOpen && phase == 2) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				stayOpen = false;
			}
			if (event.type == sf::Event::KeyPressed) {
				stayOpen = false;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				stayOpen = false;
			}
		}

		sprite2.setColor(sf::Color(255, 255, 255, i / 2));
		window.clear();
		window.draw(sprite2);
		window.display();
		i--;
		if (i <= 0) {
			stayOpen = false;
		}
	}
}

void InstructionsScreen::CharacterPage(sf::RenderWindow& window) {
	sf::Vector2<int> mou;
	vector<sf::Text> menuText;
	vector<sf::RectangleShape> menuBlock;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound click;
	buffer.loadFromFile("sounds/click.wav");
	click.setBuffer(buffer);
	sf::Vector2u winSize = window.getSize();

	//Faction, Color, About, Example Operative, Reason For Joining

	font.loadFromFile("text/olympiccarriersuperital.ttf");

	for (int i = 0; i < 8; i++) {
		menuText.push_back(sf::Text());
		menuBlock.push_back(sf::RectangleShape(sf::Vector2f(180, 50)));
	}

	menuText[0].setString("Faction A");
	menuText[1].setString("Faction B");
	menuText[2].setString("Faction C");
	menuText[3].setString("Faction D");
	menuText[4].setString("Faction E");
	menuText[5].setString("Faction F");
	menuText[6].setString("Faction G");
	menuText[7].setString("Exit");

	for (int i = 0; i < 8; i++) {
		menuBlock[i].setFillColor(sf::Color::Cyan);
		menuBlock[i].setOutlineColor(sf::Color::Red);
		menuBlock[i].setPosition(winSize.x / 2 + 180.f,
				winSize.y / 2 - 255 + (70.f * i));
		menuText[i].setCharacterSize(17);
		menuText[i].setFont(font);
		sf::FloatRect temp = menuText[i].getLocalBounds();
		menuText[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		temp = menuBlock[i].getLocalBounds();
		menuBlock[i].setOrigin(temp.left + temp.width / 2.0f,
				temp.top + temp.height / 2.0f);
		menuText[i].setPosition(winSize.x / 2 + 180.f,
				winSize.y / 2 - 255 + (70.f * i));
		menuText[i].setFillColor(sf::Color(255, 20, 147));
	}

	bool showInstruct = true;
	int menuEffect = -1;
	while (showInstruct) {
		mou = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				showInstruct = false;
			}
			if ((event.type == sf::Event::KeyPressed
					&& event.text.unicode == sf::Keyboard::Escape)
					|| (menuEffect == 7)) {
				showInstruct = false;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				for (int i = 0; i < 8; i++) {
					if (mou.x > winSize.x / 2 + 90.f
							&& mou.x < winSize.x / 2 + 270.f
							&& mou.y > winSize.y / 2 - 280 + (70.f * i)
							&& mou.y < winSize.y / 2 - 230 + (70.f * i)) {
						menuEffect = i;
						if (i != 7) {
							click.play();
						}
					}
				}
			}

		}
		for (int i = 0; i < 8; i++) {
			if (menuEffect == i) {
				menuBlock[i].setOutlineColor(sf::Color::Blue);
			} else if (mou.x > winSize.x / 2 + 90.f
					&& mou.x < winSize.x / 2 + 270.f
					&& mou.y > winSize.y / 2 - 280 + (70.f * i)
					&& mou.y < winSize.y / 2 - 230 + (70.f * i)) {
				menuBlock[i].setOutlineThickness(3);
			} else {
				menuBlock[i].setOutlineThickness(0);
				menuBlock[i].setOutlineColor(sf::Color::Red);
			}
		}
		window.clear();
		for (int i = 0; i < 8; i++) {
			window.draw(menuBlock[i]);
			window.draw(menuText[i]);
		}
		window.display();
	}
}

string InstructionsScreen::fromKtoS(const sf::Keyboard::Key& k) {
	string ret;
	switch (k) {
	case sf::Keyboard::A:
		ret = "A";
		break;
	case sf::Keyboard::B:
		ret = "B";
		break;
	case sf::Keyboard::C:
		ret = "C";
		break;
	case sf::Keyboard::D:
		ret = "D";
		break;
	case sf::Keyboard::E:
		ret = "E";
		break;
	case sf::Keyboard::F:
		ret = "F";
		break;
	case sf::Keyboard::G:
		ret = "G";
		break;
	case sf::Keyboard::H:
		ret = "H";
		break;
	case sf::Keyboard::I:
		ret = "I";
		break;
	case sf::Keyboard::J:
		ret = "J";
		break;
	case sf::Keyboard::K:
		ret = "K";
		break;
	case sf::Keyboard::L:
		ret = "L";
		break;
	case sf::Keyboard::M:
		ret = "M";
		break;
	case sf::Keyboard::N:
		ret = "N";
		break;
	case sf::Keyboard::O:
		ret = "O";
		break;
	case sf::Keyboard::P:
		ret = "P";
		break;
	case sf::Keyboard::Q:
		ret = "Q";
		break;
	case sf::Keyboard::R:
		ret = "R";
		break;
	case sf::Keyboard::S:
		ret = "S";
		break;
	case sf::Keyboard::T:
		ret = "T";
		break;
	case sf::Keyboard::U:
		ret = "U";
		break;
	case sf::Keyboard::V:
		ret = "V";
		break;
	case sf::Keyboard::W:
		ret = "W";
		break;
	case sf::Keyboard::X:
		ret = "X";
		break;
	case sf::Keyboard::Y:
		ret = "Y";
		break;
	case sf::Keyboard::Z:
		ret = "Z";
		break;
	case sf::Keyboard::Num0:
		ret = "Num0";
		break;
	case sf::Keyboard::Num1:
		ret = "Num1";
		break;
	case sf::Keyboard::Num2:
		ret = "Num2";
		break;
	case sf::Keyboard::Num3:
		ret = "Num3";
		break;
	case sf::Keyboard::Num4:
		ret = "Num4";
		break;
	case sf::Keyboard::Num5:
		ret = "Num5";
		break;
	case sf::Keyboard::Num6:
		ret = "Num6";
		break;
	case sf::Keyboard::Num7:
		ret = "Num7";
		break;
	case sf::Keyboard::Num8:
		ret = "Num8";
		break;
	case sf::Keyboard::Num9:
		ret = "Num9";
		break;
	case sf::Keyboard::Escape:
		ret = "Escape";
		break;
	case sf::Keyboard::LControl:
		ret = "LCtrl";
		break;
	case sf::Keyboard::LShift:
		ret = "LShift";
		break;
	case sf::Keyboard::LAlt:
		ret = "LAlt";
		break;
	case sf::Keyboard::LSystem:
		ret = "LSys";
		break;
	case sf::Keyboard::RControl:
		ret = "RCtrl";
		break;
	case sf::Keyboard::RShift:
		ret = "RShift";
		break;
	case sf::Keyboard::RAlt:
		ret = "RAlt";
		break;
	case sf::Keyboard::RSystem:
		ret = "RSys";
		break;
	case sf::Keyboard::Menu:
		ret = "Menu";
		break;
	case sf::Keyboard::LBracket:
		ret = "LBracket";
		break;
	case sf::Keyboard::RBracket:
		ret = "RBracket";
		break;
	case sf::Keyboard::SemiColon:
		ret = "SemiColon";
		break;
	case sf::Keyboard::Comma:
		ret = "Comma";
		break;
	case sf::Keyboard::Period:
		ret = "Period";
		break;
	case sf::Keyboard::Quote:
		ret = "Quote";
		break;
	case sf::Keyboard::Slash:
		ret = "Slash";
		break;
	case sf::Keyboard::BackSlash:
		ret = "BSlash";
		break;
	case sf::Keyboard::Tilde:
		ret = "Tilde";
		break;
	case sf::Keyboard::Equal:
		ret = "Equal";
		break;
	case sf::Keyboard::Dash:
		ret = "Dash";
		break;
	case sf::Keyboard::Space:
		ret = "Space";
		break;
	case sf::Keyboard::Return:
		ret = "Return";
		break;
	case sf::Keyboard::BackSpace:
		ret = "BSpace";
		break;
	case sf::Keyboard::Tab:
		ret = "Tab";
		break;
	case sf::Keyboard::PageUp:
		ret = "PageUp";
		break;
	case sf::Keyboard::PageDown:
		ret = "PageDown";
		break;
	case sf::Keyboard::End:
		ret = "End";
		break;
	case sf::Keyboard::Home:
		ret = "Home";
		break;
	case sf::Keyboard::Insert:
		ret = "Insert";
		break;
	case sf::Keyboard::Delete:
		ret = "Delete";
		break;
	case sf::Keyboard::Add:
		ret = "Add";
		break;
	case sf::Keyboard::Subtract:
		ret = "Subtract";
		break;
	case sf::Keyboard::Multiply:
		ret = "Multiply";
		break;
	case sf::Keyboard::Divide:
		ret = "Divide";
		break;
	case sf::Keyboard::Left:
		ret = "Left";
		break;
	case sf::Keyboard::Right:
		ret = "Right";
		break;
	case sf::Keyboard::Up:
		ret = "Up";
		break;
	case sf::Keyboard::Down:
		ret = "Down";
		break;
	case sf::Keyboard::Numpad0:
		ret = "NumP0";
		break;
	case sf::Keyboard::Numpad1:
		ret = "NumP1";
		break;
	case sf::Keyboard::Numpad2:
		ret = "NumP2";
		break;
	case sf::Keyboard::Numpad3:
		ret = "NumP3";
		break;
	case sf::Keyboard::Numpad4:
		ret = "NumP4";
		break;
	case sf::Keyboard::Numpad5:
		ret = "NumP5";
		break;
	case sf::Keyboard::Numpad6:
		ret = "NumP6";
		break;
	case sf::Keyboard::Numpad7:
		ret = "NumP7";
		break;
	case sf::Keyboard::Numpad8:
		ret = "NumP8";
		break;
	case sf::Keyboard::Numpad9:
		ret = "NumP9";
		break;
	case sf::Keyboard::F1:
		ret = "F1";
		break;
	case sf::Keyboard::F2:
		ret = "F2";
		break;
	case sf::Keyboard::F3:
		ret = "F3";
		break;
	case sf::Keyboard::F4:
		ret = "F4";
		break;
	case sf::Keyboard::F5:
		ret = "F5";
		break;
	case sf::Keyboard::F6:
		ret = "F6";
		break;
	case sf::Keyboard::F7:
		ret = "F7";
		break;
	case sf::Keyboard::F8:
		ret = "F8";
		break;
	case sf::Keyboard::F9:
		ret = "F9";
		break;
	case sf::Keyboard::F10:
		ret = "F10";
		break;
	case sf::Keyboard::F11:
		ret = "F11";
		break;
	case sf::Keyboard::F12:
		ret = "F12";
		break;
	case sf::Keyboard::F13:
		ret = "F13";
		break;
	case sf::Keyboard::F14:
		ret = "F14";
		break;
	case sf::Keyboard::F15:
		ret = "F15";
		break;
	case sf::Keyboard::Pause:
		ret = "Pause";
		break;
	case sf::Keyboard::KeyCount:
		ret = "KeyCount";
		break;
	default:
		ret = "Unknown";
		break;
	}
	return ret;
}
