#include <iostream>
#include "Game.hpp"

int main()
{
    Game *game = new Game();

    //Game Loop
    while (game->running())
    {
        game->update();
        game->render();
    }

    return 0;
}
