#include "Game.hpp"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnimies();
}

//Helps with memory leak
Game::~Game()
{
    delete this->window;
}

//Getters
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions
void Game::pollEvents()
{
    while (const std::optional event = this->window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->window->close();
            }

            else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    this->window->close();
                }
            }

            
        }
}

void Game::update()
{
    this->pollEvents();
}

/*
    -Clear old frame
    -Render
    -Display frame
    Renders the game
*/
void Game::render()
{
    //Render
    this->window->clear(sf::Color(255,255,255));//Clear old frame

    //Draw game
    this->window->draw(this->enemy);


    this->window->display();
}

//Private Functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    //Window with 16 by 9 ratio 
    // | let me pass in mult param arg
    this->videoMode.size = {1024, 576};
    this->window = new sf::RenderWindow(this->videoMode, "CMake SFML Project", 
                                    sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnimies()
{
    // this->enemy.setPosition();
    this->enemy.setSize(sf::Vector2f(64.f,64.f));
    this->enemy.setFillColor(sf::Color::Black);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}