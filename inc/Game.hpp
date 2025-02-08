#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

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
    sf::Vector2i mousePositionWindow;
    sf::Vector2f mousePositionView;

    //Game Logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Assests
    sf::Font font;
    sf::Text *uiText;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private Functions
    void initVariables();
    void initWindow();
    void initEnimies();
    void initFonts();
    void initText();
public:
    //Constructors / Destructors
    Game();
    ~Game();

    //Getters
    const bool running() const;
    const bool getEndgame() const;

    //Functions
    void spawnEnemy();
    void pollEvents();
    void updateMousePositionWindow();
    void updateEnemies();
    void updateText();
    void update();
    void renderEnemies(sf::RenderTarget &target);
    void renderText(sf::RenderTarget &target);
    void render();
};

#endif