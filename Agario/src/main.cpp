#include "Engine/Core/Application.h"
#include "Agario/Game.h"
#include "Agario/Config/Settings.h"

int main()
{
    Engine::Application app(Agario::Settings);
    Agario::Game game;

    app.Run(game);

    return 0;
}
