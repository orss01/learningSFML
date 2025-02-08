#include "Game.hpp"
#include "iostream"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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

const bool Game::getEndgame() const
{
    return this->endGame;
}


//Functions

/*
    Spawns enemies and sets their color and position

*/
void Game::spawnEnemy()
{
    this->enemy.setPosition({
        //don't want y to be random, we want it to start at the top
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f
        // static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))

    });

    int type = rand() % 5;

    switch(type)
    {
        case 0:
            this->enemy.setFillColor(sf::Color::Magenta);  
            this->enemy.setSize(sf::Vector2f(20.f,20.f)); 
            break;
        case 1:
            this->enemy.setFillColor(sf::Color::Blue);  
            this->enemy.setSize(sf::Vector2f(30.f,30.f)); 
            break;
        case 2:
            this->enemy.setFillColor(sf::Color::White);  
            this->enemy.setSize(sf::Vector2f(50.f,50.f));
            break;
        case 3:
            this->enemy.setFillColor(sf::Color::Green);  
            this->enemy.setSize(sf::Vector2f(70.f,70.f)); 
            break;
        case 4:
            this->enemy.setFillColor(sf::Color::Red);  
            this->enemy.setSize(sf::Vector2f(100.f,100.f)); 
        default:
            break;
    }

    this->enemies.push_back(this->enemy);
}

/*
    updates the ememy spawn timer and spawns eneimes
*/
void Game::updateEnemies()
{
    //Updating the timer for spawning the ememies
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the ememy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Move the ememies 
    // for(auto &e : this->enemies)
    // {
    //     e.move({0.f, 5.f});
    // }

    for(int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move({0.f, 2.f});

        // //Check if clicke on the enemy
        // if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        // {
        //     if(this->enemies[i].getGlobalBounds().contains(this->mousePositionView))
        //     {
        //         deleted = true;

        //         //Gain points
        //         this->points += 10.f;
        //     }
        // }

        //If the enemy is at the bottom of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health : " << this->health << "\n" << std::endl; 
        }

        // //Final Delete
        // if(deleted)
        // {
        //     this->enemies.erase(this->enemies.begin() + i);
        // }
    }

    //Check if clicke on the enemy
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if(!this->mouseHeld)
        {
            this->mouseHeld = true;
            bool deleted = false;

            for(size_t i = 0; i < this->enemies.size() && !deleted; i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePositionView))
                {
                    deleted = true;
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                    {
                        this->points += 10;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)
                    {
                        this->points += 7;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::White)
                    {
                        this->points += 5;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Green)
                    {
                        this->points += 3;
                    }
                    else
                    {
                        this->points += 1;
                    }
                    this->enemies.erase(this->enemies.begin() + i);
                    //Gain points
                    std::cout << "Points : " << this->points << "\n" << std::endl; 
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::renderEnemies(sf::RenderTarget &target)
{
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << 
        "\nHealth: " << this->health;

    this->uiText->setString(ss.str());
}

void Game::renderText(sf::RenderTarget &target)
{
    this->window->draw(*this->uiText);
}

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
    if(!this->endGame)
    {
        this->updateMousePositionWindow();
        this->updateText();
        this->updateEnemies();
    }
    if(this->health <= 0)
    {
        this->endGame = true;
    }    
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
    this->window->clear(sf::Color(0,0,0));//Clear old frame

    //Draw game
    this->renderEnemies(*this->window);

    this->renderText(*this->window);


    this->window->display();
}


/*
    Updates the mouse position realtive to the window (Vector2i)
*/
void Game::updateMousePositionWindow()
{
    this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
    this->mousePositionView = this->window->mapPixelToCoords(this->mousePositionWindow);

    //Update Mouse position
    //Relative to the screen
    // std::cout << "Mouse Pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";

    //Relative to the window
    // *this->window, have to dereference the window
    // std::cout << "Mouse Pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
}

//Private Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 10;
    this->endGame = false;
}

void Game::initWindow()
{
    //Window with 16 by 9 ratio 
    // | let me pass in mult param arg
    this->videoMode.size = {1024u, 576u};
    this->window = new sf::RenderWindow(this->videoMode, "CMake SFML Project", 
                                    sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnimies()
{
    // this->enemy.setPosition({10.f,10.f});
    this->enemy.setSize(sf::Vector2f(64.f,64.f));
    // this->enemy.setFillColor(sf::Color::Black);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
}

void Game::initFonts()
{
    if(!this->font.openFromFile("assets/fonts/Comic_Sans_MS/Comic-Sans-MS.ttf"))
    {
        std::cout << "Font Error" << std::endl;
        this->window->close();
    }
}

void Game::initText()
{
    this->uiText = new sf::Text(this->font);
    this->uiText->setCharacterSize(24);
    this->uiText->setFillColor(sf::Color::White);
    this->uiText->setString("Hello World!");
}