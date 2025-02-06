#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

/*
    Game class that acts as the game engine
*/

class Game
{
private:
    //Fields
    sf::RenderWindow *window;
    sf::VideoMode videoMode;

    //Game objects
    sf::RectangleShape enemy;

    //Private Functions
    void initVariables();
    void initWindow();
    void initEnimies();
public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Getters
    const bool running() const;

    //Functions
    void pollEvents();
    void update();
    void render();
};

#endif