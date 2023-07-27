/* #include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
	
	//game logic
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->gridSizeF = 100.f;
	this->gridSizeU = static_cast<unsigned>(gridSizeF);

	sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

	this->vidMode.height = 540;
	this->vidMode.width = 960;
	this->window = new sf::RenderWindow(this->vidMode, "SoT Map");
	this->window->setFramerateLimit(60);
}
void Game::initView()
{
	sf::View view;
	view.setSize(500, 500);
	//view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

void Game::initBoats()
{
	this->boat.setSize(sf::Vector2f(100.f, 100.f));
	this->boat.setFillColor(sf::Color::Cyan);
	this->boat.setOutlineColor(sf::Color::Green);
	this->boat.setOutlineThickness(1.f);
}

//constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initBoats();
}
Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


//functions

//Spawns enemies and sets their color and positions.
void Game::spawnEnemy()
{
	this->boat.setPosition(50, 50);

	this->boat.setFillColor(sf::Color::Green);

	this->boats.push_back(this->boat);


}


//Updates the mouse positions relative to the window (Vector2i)
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
	if (this->boats.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	for (auto& e : this->boats) 
	{
		e.move(0.f, 5.f);
	}
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	//Rendering all enemies
	for (auto& e : this->boats)
	{
		this->window->draw(e);
	}
}

//renders the game objects
void Game::render() 
{
	//clear old frame
	this->window->clear();

	//draw game objects
	this->renderEnemies();
	//this->window.draw(boat1);

	//display frame in window
	this->window->display();
}*/