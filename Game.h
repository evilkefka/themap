/*
#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>



	//Class that acts as teh game engine

class Game
{
private:
	//window
	sf::RenderWindow* window;
	sf::VideoMode vidMode;
	sf::Event ev;
	float gridSizeF;
	unsigned gridSizeU;

	//Mouse positions
	sf::Vector2i mousePosWindow;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Game objects
	std::vector<sf::RectangleShape> boats;
	sf::RectangleShape boat;

	//private functions
	void initVariables();
	void initWindow();
	void initView();
	void initBoats();
public:
	//Constructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions()
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();


	void renderEnemies();
	void render();
};

*/