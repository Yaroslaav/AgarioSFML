#include "../../Engine/include/Engine/Core/Application.h"
#include "Agario/Game.h"

int main()
{
    Engine::Application app(1280, 720, "Agario");
    Agario::Game game;

    app.Run(game);

    return 0;
}