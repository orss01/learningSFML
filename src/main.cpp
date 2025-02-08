#include <iostream>
#include "Game.hpp"

int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    Game *game = new Game();

    //Game Loop
    while (game->running() && !game->getEndgame())
    {
        game->update();
        game->render();
    }

    return 0;
}
