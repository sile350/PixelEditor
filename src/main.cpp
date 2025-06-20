#include <SDL.h>
#include <stdio.h>

#include "Engine.h"

int main(int argc, char* argv[]) 
{
    Engine::Init(1000, 800);

    while (Engine::WindowIsRunning()) 
    {
        Engine::PollEvent();
        Engine::Render();
    }

    Engine::Cleanup();
    return 0;
}